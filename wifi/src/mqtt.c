#include "mqtt.h"

//static uint32_t mqtt_encode_lenght(uint32_t size);

void mqtt_ctor(mqtt_t * const me,
               wizfi_t * const client,
               uint8_t *buffer,
               uint32_t buffer_size,
               MQTT_callback callback)
{
    me->client = client;
    me->state = MQTT_DISCONNECTED;
    me->keep_alive = 6000;
    me->buffer = buffer;
    me->buffer_size = buffer_size;
    me->callback = callback;
    me->last_in = 0;
    me->last_out = 0;
    me->ping = PING_FALSE;
}

int32_t mqtt_connect(mqtt_t *const me,
                     char const *client_id,
                     const char *address,
                     uint32_t port)
{
    uint32_t index = 0;
    int32_t result;
    result = wizfi360_start_client(me->client, address, port);

    if(result == WIZFI360_OK)
    {
        log_info("MQTT client attempting to connect to broker %s:%i", address, port);

        uint16_t id_lenght = strlen(client_id);

        /*Fixed header*/
        me->buffer[index++] = CONNECT;
        /*Remaining lenght*/
        me->buffer[index++] = 12 + id_lenght;
        /*Protocol name*/
        me->buffer[index++] = 0x00;
        me->buffer[index++] = 0x04;
        me->buffer[index++] = 'M';
        me->buffer[index++] = 'Q';
        me->buffer[index++] = 'T';
        me->buffer[index++] = 'T';
        /*Protocol level MQTT 3.1.1*/
        me->buffer[index++] = 0x04;
        /*Connect flags. TODO: User parameter*/
        me->buffer[index++] = CONNECT_CLEAN_SESSION;
        /*Keep alive bytes. TODO: User parameter*/
        uint16_t keep_alive = me->keep_alive / 1000;
        me->buffer[index++] = (keep_alive >> 8);
        me->buffer[index++] = (keep_alive & 0x0F);

        /*Payload data*/
        /*Client ID*/
        me->buffer[index++] = (id_lenght >> 8);
        me->buffer[index++] = (id_lenght & 0xFF);
        for(uint32_t i = 0; i < id_lenght; i++)
        {
            me->buffer[index++] = client_id[i];
        }

        /*TODO: Will Topic*/
        /*TODO: Will Message*/
        /*TODO: User Name*/
        /*TODO: Password*/

        /*Write data to the network*/
        wizfi360_write(me->client, me->buffer, index);

        me->last_in = SysTick_millis();
        me->last_out = SysTick_millis();

        /*Wait for CONNACK from broker*/
        uint8_t buff[12];
        uint32_t count = wizfi360_read(me->client,  buff, 12);
        if(count == 4)
        {
            /*We got something, at least is the right
             * amount of data, check it*/
            if(buff[3] == CONNECTION_ACCEPTED)
            {
                me->last_in = SysTick_millis();
                me->ping = PING_FALSE;
                me->state = MQTT_CONNECTED;
                log_info("MQTT client connected to %s:%i", address, port);
            }
        }
    }

    if(me->state != MQTT_CONNECTED)
    {
        log_error("MQTT client failed to connect to broker %s:%i", address, port);
    }

    return result;
}

int32_t mqtt_publish(mqtt_t * const me, char const *topic,
                     uint8_t const *payload, uint32_t payload_size)
{
    uint32_t index = 0;
    uint32_t status = MQTT_FAILED_PUBLISH;

    if(me->state == MQTT_CONNECTED)
    {
        log_info("MQTT client publishing to %s topic", topic);
        uint16_t topic_lenght = strlen(topic);

        /*Check that this packet fits inside the buffer*/

        /*Fixed header*/
        me->buffer[index++] = PUBLISH | PUBLISH_QOS_0;
        /*Remaining length. 2 + topic_lenght + 2 + payload_size*/
        me->buffer[index++] = topic_lenght  + payload_size + 4;

        /*Topic name*/
        me->buffer[index++] = (topic_lenght >> 8);
        me->buffer[index++] = (topic_lenght & 0xFF);
        for(uint32_t i = 0; i < topic_lenght; i++)
        {
            me->buffer[index++] = topic[i];
        }

        /*me->buffer identifier*/
        me->buffer[index++] = 0x00;
        me->buffer[index++] = 0x0A;

        /*Payload*/
        for(uint32_t i = 0; i < payload_size; i++)
        {
            me->buffer[index++] = payload[i];
        }

        wizfi360_write(me->client, me->buffer, index);
        me->last_out = SysTick_millis();
        status = MQTT_OK;

        log_info("MQTT client publish success into %s topic", topic);
    }
    else
    {
        log_warn("MQTT client failed to publish into %s topic", topic);
    }

    return status;
}

int32_t mqtt_subscribe(mqtt_t * const me, char const *topic)
{
    uint32_t index = 0;
    int32_t status = MQTT_FAILED_SUBSCRIBE;

    if(me->state == MQTT_CONNECTED)
    {
        uint16_t topic_length = strlen(topic);

        /*Fixed header*/
        me->buffer[index++] = SUBSCRIBE;
        /*Remaining length*/
        me->buffer[index++] = topic_length + 5;

        /*Payload identifier*/
        me->buffer[index++] = 0x00;
        me->buffer[index++] = 0x0A;

        /*Payload*/
        me->buffer[index++] = (topic_length >> 8);
        me->buffer[index++] = (topic_length & 0xFF);
        for(uint32_t i = 0; i < topic_length; i++)
        {
            me->buffer[index++] = topic[i];
        }
        /*QoS*/
        me->buffer[index++] = 0x00;

        /*Write SUBSCRIBE me->buffer*/
        wizfi360_write(me->client, me->buffer, index);

        /*Wait for SUBACK from broker*/
        uint32_t count = wizfi360_read(me->client,  me->buffer, 64);
        if(count == 5)
        {
            /*We got something, at least is the right
             * amount of data, check it*/
            if(me->buffer[4] == SUBSCRIBE_SUCCESS_QOS_0)
            {
                status = MQTT_OK;
                log_info("MQTT client subscribed to topic %s", topic);
            }
        }
    }

    if(status != MQTT_OK)
    {
        log_warn("MQTT client failed to subscribed to topic %s", topic);
    }

    return status;
}

int32_t mqtt_loop(mqtt_t * const me)
{
    char topic[32];
    uint8_t type;
    uint32_t count;

    while(me->state == MQTT_CONNECTED)
    {
        /*Send ping if keep alive timeout has been reached*/
        uint32_t t = SysTick_millis();
        if(((t - me->last_in) > me->keep_alive) ||
            ((t - me->last_out) > me->keep_alive))
        {
            if(me->ping)
            {
                me->state = MQTT_CONNECTION_TIMEOUT;
                break;
            }
            else
            {
                /*Create ping request packet*/
                me->buffer[0] = PINGREQ;
                me->buffer[1] = 0;
                wizfi360_write(me->client, me->buffer, 2);

                /*Set time stamps and ping response*/
                me->last_out = t;
                me->last_in = t;
                me->ping = PING_TRUE;
            }
        }

        /*Read data*/
        count = wizfi360_read(me->client, me->buffer, me->buffer_size);
        if(count > 0)
        {
            me->last_in = t;
            type = me->buffer[0] & 0xF0;

            switch(type)
            {
            case PUBLISH:
                {
                    /*Remaining length byte*/
                    uint8_t lenght = me->buffer[1];

                    /*Topic length*/
                    uint16_t topic_lenght = (me->buffer[2] << 8) | me->buffer[3];

                    /*Topic data*/
                    for(uint32_t i = 0; i < topic_lenght; i++)
                    {
                        topic[i] = me->buffer[i + 4];
                    }
                    topic[topic_lenght] = 0;

                    /*Payload length*/
                    uint16_t payload_length = lenght - topic_lenght;

                    if(me->callback)
                    {
                        me->callback(topic,
                                     me->buffer + topic_lenght + 4,
                                     payload_length);
                    }
                }
                break;
            case PINGREQ:
                me->buffer[0] = PINGRESP;
                me->buffer[1] = 0;
                wizfi360_write(me->client, me->buffer, 2);
                break;
            case PINGRESP:
                me->ping = PING_FALSE;
                break;
            }
        }
    }

    return me->state;
}

/*
static uint32_t mqtt_encode_lenght(uint32_t lenght)
{
    uint8_t byte;
    uint8_t byte_buff[4] = {0};
    uint32_t index;
    uint32_t encoded_length;

    do
    {
        byte = lenght % 128;
        lenght = lenght / 128;
        if(lenght > 0)  byte |= 0x80;

        byte_buff[index++] = byte;
    }while(lenght > 0);

    encoded_length = (byte_buff[3] << 24) |
                     (byte_buff[2] << 16) |
                     (byte_buff[1] << 8) |
                     (byte_buff[0] << 0);

    return encoded_length;
}
*/
