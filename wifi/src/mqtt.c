/**
 * @dir wifi/src
 * @brief WiFi source code
 * @details More details to be displayed on the folder's page.
 * 
 * @file mqtt.c
 * @authors Alejandro Martinez (mailto:amartinezacosta@miners.utep.edu)
 * @authors Jesus Minjares (mailto:jminjares4@miners.utep.edu)
 * @brief MQTT protocol source code 
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "mqtt.h"

//static uint32_t mqtt_encode_lenght(uint32_t size);


/******************************************************************
 * \brief Mqtt constructor
 * 
 * Detailed description starts here 
 * @param me            pointer to mqttt object
 * @param client        pointer to wizfi object
 * @return None
 *******************************************************************/
void mqtt_ctor(mqtt_t * const me, wizfi_t * const client)
{
    me->client = client;
    me->state = MQTT_DISCONNECTED;
    me->keep_alive = 60;
}

/******************************************************************
 * \brief Mqtt register
 * 
 * Detailed description starts here 
 * @param me            pointer to mqttt object
 * @param topic         topic string
 * @param mqtt_callback callback 
 * @return int32_t      status
 *******************************************************************/
int32_t mqtt_register(mqtt_t * const me,
                      char const *topic,
                      void(*mqtt_callback)(uint8_t const *, uint32_t))
{
    uint32_t count = me->callbacks_count;
    if(count > MQTT_MAX_CALLBACKS) return -1;

    me->callbacks[count].topic = topic;
    me->callbacks[count].callback = mqtt_callback;

    return 0;
}

/******************************************************************
 * \brief Mqtt connect
 * 
 * Detailed description starts here 
 * @param me            pointer to mqttt object
 * @param client_id     client id
 * @param address       address
 * @param port          port number 
 * @return int32_t      status
 *******************************************************************/
int32_t mqtt_connect(mqtt_t *const me,
                     char const *client_id,
                     const char *address,
                     uint32_t port)
{
    uint8_t packet[64];
    uint32_t index = 0;
    int32_t result;
    result = wizfi360_start_client(me->client, address, port);

    if(result == WIZFI360_OK)
    {
        log_info("MQTT client attempting to connect to broker %s:%i", address, port);

        uint16_t id_lenght = strlen(client_id);

        /*Fixed header*/
        packet[index++] = CONNECT;
        /*Remaining lenght*/
        packet[index++] = 12 + id_lenght;
        /*Protocol name*/
        packet[index++] = 0x00;
        packet[index++] = 0x04;
        packet[index++] = 'M';
        packet[index++] = 'Q';
        packet[index++] = 'T';
        packet[index++] = 'T';
        /*Protocol level MQTT 3.1.1*/
        packet[index++] = 0x04;
        /*Connect flags. TODO: User parameter*/
        packet[index++] = CONNECT_CLEAN_SESSION;
        /*Keep alive bytes. TODO: User parameter*/
        packet[index++] = (me->keep_alive >> 8);
        packet[index++] = (me->keep_alive & 0x0F);

        /*Payload data*/
        /*Client ID*/
        packet[index++] = (id_lenght >> 8);
        packet[index++] = (id_lenght & 0xFF);
        for(uint32_t i = 0; i < id_lenght; i++)
        {
            packet[index++] = client_id[i];
        }

        /*TODO: Will Topic*/
        /*TODO: Will Message*/
        /*TODO: User Name*/
        /*TODO: Password*/

        /*Write data to the network*/
        wizfi360_write(me->client, packet, index);

        /*Wait for CONNACK from broker*/
        uint8_t buff[12];
        uint32_t count = wizfi360_read(me->client,  buff, 12);
        if(count == 4)
        {
            /*We got something, at least is the right
             * amount of data, check it*/
            if(buff[3] == CONNECTION_ACCEPTED)
            {
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

/******************************************************************
 * \brief Mqtt publish
 * 
 * Detailed description starts here 
 * @param me            pointer to mqttt object
 * @param topic         topic string
 * @param payload       payload array
 * @param payload_size  payload_size
 * @return int32_t      status
 *******************************************************************/
int32_t mqtt_publish(mqtt_t * const me, char const *topic,
                     uint8_t const *payload, uint32_t payload_size)
{
    uint8_t packet[64];
    uint32_t index = 0;
    uint32_t status = MQTT_FAILED_PUBLISH;

    if(me->state == MQTT_CONNECTED)
    {
        log_info("MQTT client publishing to %s topic", topic);
        uint16_t topic_lenght = strlen(topic);

        /*Fixed header*/
        packet[index++] = PUBLISH | PUBLISH_QOS_0;
        /*Remaining length. 2 + topic_lenght + 2 + payload_size*/
        packet[index++] = topic_lenght  + payload_size + 4;

        /*Topic name*/
        packet[index++] = (topic_lenght >> 8);
        packet[index++] = (topic_lenght & 0xFF);
        for(uint32_t i = 0; i < topic_lenght; i++)
        {
            packet[index++] = topic[i];
        }

        /*Packet identifier*/
        packet[index++] = 0x00;
        packet[index++] = 0x0A;

        /*Payload*/
        for(uint32_t i = 0; i < payload_size; i++)
        {
            packet[index++] = payload[i];
        }

        wizfi360_write(me->client, packet, index);
        status = MQTT_OK;

        log_info("MQTT client publish success into %s topic", topic);
    }
    else
    {
        log_warn("MQTT client failed to publish into %s topic", topic);
    }

    return status;
}

/******************************************************************
 * \brief Mqtt subscribe
 * 
 * Detailed description starts here 
 * @param me            pointer to mqttt object
 * @param topic         topic string
 * @return int32_t      status
 *******************************************************************/
int32_t mqtt_subscribe(mqtt_t * const me, char const *topic)
{
    uint8_t packet[64];
    uint32_t index = 0;
    int32_t status = MQTT_FAILED_SUBSCRIBE;

    if(me->state == MQTT_CONNECTED)
    {
        uint16_t topic_length = strlen(topic);

        /*Fixed header*/
        packet[index++] = SUBSCRIBE;
        /*Remaining length*/
        packet[index++] = topic_length + 5;

        /*Packet identifier*/
        packet[index++] = 0x00;
        packet[index++] = 0x0A;

        /*Payload*/
        packet[index++] = (topic_length >> 8);
        packet[index++] = (topic_length & 0x0F);
        for(uint32_t i = 0; i < topic_length; i++)
        {
            packet[index++] = topic[i];
        }
        /*QoS*/
        packet[index++] = 0x00;

        /*Write SUBSCRIBE packet*/
        wizfi360_write(me->client, packet, index);

        /*Wait for SUBACK from broker*/
        uint8_t buff[12];
        uint32_t count = wizfi360_read(me->client,  buff, 12);
        if(count == 5)
        {
            /*We got something, at least is the right
             * amount of data, check it*/
            if(buff[4] == SUBSCRIBE_SUCCESS_QOS_0)
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


/******************************************************************
 * \brief Mqtt loop
 * 
 * Detailed description starts here 
 * @param me            pointer to mqttt object
 * @return int32_t      status
 *******************************************************************/
int32_t mqtt_loop(mqtt_t * const me)
{
    uint8_t data[64];
    char topic_buff[32];
    uint8_t type;
    uint16_t topic_lenght;
    uint16_t payload_length;

    uint32_t count;

    while(me->state == MQTT_CONNECTED)
    {
        /*Send ping if keep alive timeout has been reached*/
        //uint32_t t0 = SysTick_millis();

        /*Read data*/
        count = wizfi360_read(me->client, data, 64);
        if(count > 0)
        {
            type = data[0] & 0xF0;

            switch(type)
            {
            case PUBLISH:
                {
                    /*Remaining length byte*/
                    /*TODO: Variable length for more than 1 byte*/
                    uint32_t index = 1;
                    //uint8_t lenght = data[index++];

                    /*Topic*/
                    /*Topic length*/
                    topic_lenght = (data[index++] << 8);
                    topic_lenght |= data[index++];

                    /*Topic data*/
                    for(uint32_t i = 0; i < topic_lenght; i++)
                    {
                        topic_buff[i] = data[index++];
                    }
                    topic_buff[topic_lenght] = 0;

                    /*Payload*/
                    /*Payload length*/
                    payload_length = (data[index++] << 8);
                    payload_length |= data[index++];

                    /*Check if topic callback exists*/
                    for(uint32_t i = 0; i < me->callbacks_count; i++)
                    {
                        if(!strcmp(me->callbacks[i].topic, topic_buff))
                        {
                            me->callbacks[i].callback(data + index, payload_length);
                            break;
                        }
                    }
                }
                break;
            case PINGREQ:
                break;
            case PINGRESP:
                break;
            }
        }
    }

    return MQTT_OK;
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
