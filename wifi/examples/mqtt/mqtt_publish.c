#include "wizfi360.h"
#include "mqtt.h"
#include "logger.h"

#define MQTT_BUFFER_SIZE    256
uint8_t MQTT_buffer[MQTT_BUFFER_SIZE];

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

    while(1)
    {
        mqtt_publish(&mqtt, "hello/world", "hello mqtt", 10);
        SysTick_delay(1000);
    }
}

void HAL_assert(const char *module, const int line)
{
    while(1)
    {
    }
}
