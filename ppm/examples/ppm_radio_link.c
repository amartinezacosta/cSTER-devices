/**
 * @file ppm_radio_link.c
 * @authors Alejandro Martinez (mailto:amartinezacosta@miners.utep.edu)
 * @authors Jesus Minjares (mailto:jminjares4@miners.utep.edu)
 * @brief PPM Radio Link example code
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <ppm.h>
#include <logger.h>
#include <SysTick_HAL.h>

int main(void)
{
    /*Find PPM device*/
    dev_t *capture = HAL_find_name("CAP_0");
    HAL_ASSERT_MODULE_NAME(capture, "main");

    /*Create an instance of PPM object*/
    ppm_t ppm;
    ppm_ctor(&ppm , capture, 8);

    uint32_t channels[8];
    while(1)
    {
        /*Read PPM channels*/
        ppm_get_channels(&ppm, channels);

        /*Log information*/
        log_info("%i,%i,%i,%i,%i,%i,%i,%i",
                 channels[0], channels[1],
                 channels[2], channels[3],
                 channels[4], channels[5],
                 channels[6], channels[7]);
        
        /*10 millisecond delay*/
        SysTick_delay(10);
    }
}

void HAL_assert(const char *module, const int line)
{
    while(1)
    {

    }
}
