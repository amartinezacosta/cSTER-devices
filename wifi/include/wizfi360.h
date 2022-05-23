/**
 * @file wizfi360.h
 * @authors Alejandro Martinez (mailto:amartinezacosta@miners.utep.edu)
 * @authors Jesus Minjares (mailto:jminjares4@miners.utep.edu)
 * @brief Wizfi360 WiFi Module library
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef WIZFI360_H_
#define WIZFI360_H_

#include <UART_HAL.h>
#include <SysTick_HAL.h>
#include <ustdio.h>
#include <logger.h>
#include <stdlib.h>

#define WIZFI360_TIMEOUT_ERROR              -2
#define WIZFI360_ERROR_BUFFER_OVERRRUN      -1
#define WIZFI360_OK                         0
#define WIZFI360_ERROR                      1
#define WIZFI360_FAIL                       2
#define WIZFI360_SEND_OK                    3
#define WIZFI360_CONNECT                    4
#define WIZFI360_DELIMITER_FOUND            5

/******************************************************************
 * \struct wizfi_t wizfi360.h 
 * \brief Wizfi object
 * 
 * ### Example
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.c
 * typedef struct{
 *      char_devio_t com;
 * }wizfi_t;
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
typedef struct
{
    char_devio_t com;
}wizfi_t;

void wizfi360_ctor(wizfi_t * const me, dev_t * const dev);

int32_t wizfi360_send_wait(wizfi_t * const me,
                           char const *cmd,
                           char const *delimiter,
                           uint32_t timeout);

int32_t wizfi360_connect(wizfi_t * const me, char const *ssid, char const *password);
int32_t wizfi360_start_server(wizfi_t * const me, uint16_t port, uint8_t sock);
int32_t wizfi360_start_client(wizfi_t * const me, char const *address, uint16_t port);

uint32_t wizfi360_write(wizfi_t * const me, uint8_t const *data, uint32_t size);
uint32_t wizfi360_read(wizfi_t * const me, uint8_t *data, uint32_t size);
uint32_t wizfi360_available(wizfi_t * const me);


#endif
