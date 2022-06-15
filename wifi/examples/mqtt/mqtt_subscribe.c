#include "wizfi360.h"
#include "mqtt.h"
#include "logger.h"

#define MQTT_BUFFER_SIZE    256
uint8_t MQTT_buffer[MQTT_BUFFER_SIZE];

void callback(char const *topic, uint8_t const * const payload, uint32_t const size)
{
    log_info("Topic: %s, payload size: %i, payload: %s", topic, size, payload);
}

int main(void)
{
    dev_t *uart = HAL_find_name("UART_1");
    HAL_ASSERT_MODULE_NAME(uart, "main");

    /*Construct and connect wizfi module to an access point (router)*/
    wizfi_t wifi;
    mqtt_t mqtt;

    wizfi360_ctor(&wifi, uart);
    mqtt_ctor(&mqtt, &wifi,
              MQTT_buffer,
              MQTT_BUFFER_SIZE,
              &callback);

    while(wizfi360_connect(&wifi, "SSID", "password") != WIZFI360_OK);

    mqtt_connect(&mqtt, "wizfi", "ip_address", 1883);

    //char *str = "hello world";
    mqtt_subscribe(&mqtt, "hello/world");

    while(1)
    {
        mqtt_loop(&mqtt);
    }
}

void HAL_assert(const char *module, const int line)
{
    while(1)
    {
    }
}
