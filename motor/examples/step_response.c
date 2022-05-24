/**
 * @file step_response.c
 * @authors Alejandro Martinez (mailto:amartinezacosta@miners.utep.edu)
 * @authors Jesus Minjares (mailto:jminjares4@miners.utep.edu)
 * @brief Step response example code
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <logger.h>
#include <SysTick_HAL.h>
#include <math.h>

#include <motor.h>
#include <pid.h>

#define DATA_POINTS 256

uint32_t time[DATA_POINTS];

/*Outputs*/
int32_t encoder_position[DATA_POINTS];
int32_t encoder_delta[DATA_POINTS];

/*Inputs*/
uint32_t pwm_input[DATA_POINTS];

int main(void)
{
    /*Find from device table*/
    dev_t *pwm0 = HAL_find_name("PWM_0");
    dev_t *pwm1 = HAL_find_name("PWM_1");
    dev_t *gpio0 = HAL_find_name("GPIO_0");
    dev_t *gpio1 = HAL_find_name("GPIO_1");
    dev_t *gpio_sleep = HAL_find_name("GPIO_8");

    dev_t *enableSwReg = HAL_find_name("GPIO_13");

    HAL_ASSERT_MODULE_NAME(enableSwReg, "main");

    /*Assert all pointers*/
    HAL_ASSERT_MODULE_NAME(pwm0 &&
                           pwm1 &&
                           gpio0 &&
                           gpio1 &&
                           gpio_sleep, "motor");

    GPIO_open(enableSwReg, HAL_CONFIG_DEFAULT);
    GPIO_write(enableSwReg, GPIO_STATE_HIGH);

    /*Instantiate motor_t object*/
    motor_t motor0;
    motor_ctor(&motor0, pwm0, pwm1, gpio0, gpio1, gpio_sleep);

    /*Enable motor*/
    motor_enable(&motor0);

    /*Initialize time to 0*/
    uint32_t t0 = 0.0;
    uint32_t dt = 0.0;
    uint32_t t = 0;
    uint32_t index = 0;

    /*Step input*/
    uint32_t step = 40000;

    /*Perform experiment until set point has been reached*/
    while(t < 3000)
    {
        t0 = SysTick_millis();

        /*Motor position and motor delta position*/
        int32_t ticks = motor_position(&motor0);
        int32_t delta = motor_position_delta(&motor0);

        /*Motor direction*/
        motor_speed(&motor0, step, COUNTER_CLOCKWISE);

        /*Save data for logging*/
        if(index < DATA_POINTS)
        {
            /*Save data*/
            time[index] = t;
            pwm_input[index] = step;
            encoder_position[index] = ticks;
            encoder_delta[index] = delta; 

            /*Increment data index*/
            index++;
        }

        SysTick_delay(30);
        dt = SysTick_millis() - t0;
        t += dt;
    }

    /*Stop motor*/
    motor_speed(&motor0, 0, 0);

    /*Experiment done, dump all data to serial console*/
    log_raw("time,pwm_input,ticks,delta_ticks");
    for(uint32_t i = 0; i < index; i++)
    {
        log_raw("%i,%i,%i,%i", time[i], 
                pwm_input[i], 
                encoder_position[i],
                encoder_delta[i]);
    }

    while(1)
    {

    }
}

void HAL_assert(const char *module, const int line)
{
    while(1)
    {

    }
}
