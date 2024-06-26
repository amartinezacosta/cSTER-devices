/**
 * @dir wifi
 * @brief This folder contains all files related to WiFi
 * @details More details to be displayed on the folder's page.
 * 
 * @dir wifi/include
 * @brief WiFi library
 * @details More details to be displayed on the folder's page.
 * 
 * @file mqtt.h
 * @authors Alejandro Martinez (mailto:amartinezacosta@miners.utep.edu)
 * @authors Jesus Minjares (mailto:jminjares4@miners.utep.edu)
 * @brief MQTT protocol library
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef MQTT_H_
#define MQTT_H_

#include "wizfi360.h"

/*MQTT FUNCTION RETURN CODES*/
#define MQTT_CONNECTION_TIMEOUT -4
#define MQTT_FAILED_SUBSCRIBE   -3
#define MQTT_FAILED_PUBLISH     -2
#define MQTT_DISCONNECTED       -1
#define MQTT_OK                 0
#define MQTT_CONNECTED          1

/*MQTT CONNACK RETURN CODES*/
#define CONNECTION_ACCEPTED         0
#define UNACCEPTABLE_PROTOCOL       1
#define IDENTIFIER_REJECTED         2
#define SERVER_UNAVAILABLE          3
#define BAD_USER_PASSWORD           4
#define NOT_AUTHORIZED              5

/*MQTT SUBACK RETURN CODES*/
#define SUBSCRIBE_SUCCESS_QOS_0     0x00
#define SUBSCRIBE_SUCCESS_QOS_1     0x01
#define SUBSCRIBE_SUCCESS_QOS_2     0x02
#define SUBSCRIBE_FAILURE           0x80

/*MQTT CONTROL PACKET TYPES*/
#define CONNECT         0x10
#define CONNACK         0x20
#define PUBLISH         0x30
#define PUBACK          0x40
#define PUBREC          0x50
#define PUBREL          0x60
#define PUBCOMP         0x70
#define SUBSCRIBE       0x82
#define SUBACK          0x90
#define UNSUBSCRIBE     0xA0
#define UNSUBACK        0xB0
#define PINGREQ         0xC0
#define PINGRESP        0xD0
#define DISCONNECT      0xE0

/*MQTT CONTROL PACKET FLAGS*/
#define PUBLISH_DUP     0x08
#define PUBLISH_QOS_0   0x00
#define PUBLISH_QOS_1   0x02
#define PUBLISH_QOS_2   0x04
#define PUBLISH_RETAIN  0x01

/*MQTT CONNECT FLAGS*/
#define CONNECT_USERNAME        0x80
#define CONNECT_PASSWORD        0x40
#define CONNECT_WILL_RETAIN     0x20
#define CONNECT_WILL_QOS_0      0x00
#define CONNECT_WILL_QOS_1      0x08
#define CONNECT_WILL_QOS_2      0x10
#define CONNECT_WILL_FLAG       0x04
#define CONNECT_CLEAN_SESSION   0x02

/*PING*/
#define PING_FALSE              0
#define PING_TRUE               1

typedef void(*MQTT_callback)(char const *,
                             uint8_t const * const,
                             uint32_t const);

/******************************************************************
 * \struct mqtt_t mqtt.h 
 * \brief Mqtt object
 * 
 * ### Example
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.c
 * typedef struct{
 *      wizfi_t *client;
 *      uint32_t state;
 *      uint32_t callbacks_count;
 *      mqtt_callback_t callbacks[MQTT_MAX_CALLBACKS]l
 * }mqtt_t;
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
typedef struct
{
    wizfi_t *client;
    uint32_t state;
    uint16_t keep_alive;
    uint32_t last_in;
    uint32_t last_out;
    uint8_t ping;
    uint8_t *buffer;
    uint32_t buffer_size;
    MQTT_callback callback;
}mqtt_t;

void mqtt_ctor(mqtt_t * const me,
               wizfi_t * const client,
               uint8_t *buffer,
               uint32_t buffer_size,
               MQTT_callback callback);
               
int32_t mqtt_connect(mqtt_t *const me,
                     char const *client_id,
                     const char *address,
                     uint32_t port);

int32_t mqtt_publish(mqtt_t * const me, char const *topic,
                     uint8_t const *payload, uint32_t payload_size);
int32_t mqtt_subscribe(mqtt_t * const me, char const *topic);
int32_t mqtt_loop(mqtt_t *const me);


#endif
