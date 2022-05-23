/**
 * @file motor_with_pid.c
 * @authors Alejandro Martinez (mailto:amartinezacosta@miners.utep.edu)
 * @authors Jesus Minjares (mailto:jminjares4@miners.utep.edu)
 * @brief Motor device example using PID controller driver
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <logger.h>
#include "motor.h"
#include "pid.h"
#include "SysTick_HAL.h"


int main(void)
{
    /*Find from device table*/
    dev_t *pwm0 = HAL_find_name("PWM_0");
    dev_t *pwm1 = HAL_find_name("PWM_1");
    dev_t *gpio0 = HAL_find_name("GPIO_0");
    dev_t *gpio1 = HAL_find_name("GPIO_1");
    dev_t *gpio_sleep = HAL_find_name("GPIO_8");


    dev_t *enableSwReg = HAL_find_name("GPIO_13");
    GPIO_open(enableSwReg, HAL_CONFIG_DEFAULT);
    GPIO_write(enableSwReg, GPIO_STATE_HIGH);
    HAL_ASSERT_MODULE_NAME(enableSwReg, "main");

    /*Assert all pointers*/
    HAL_ASSERT_MODULE_NAME(pwm0 &&
                           pwm1 &&
                           gpio0 &&
                           gpio1 &&
                           gpio_sleep, "motor");

    /*Instantiate motor_t object*/
    motor_t motor0;
    motor_ctor(&motor0, pwm0, pwm1, gpio0, gpio1, gpio_sleep);

    /*Set default parameters for PID*/
    PID_params_t default_params =
    {  
        .kp = 1.0,
        .ki = 0.0,
        .kd = 0.0,
        .error_max_threshold = 10.0,
        .error_min_threshold = -10.0,
        .max_integral = 1000.0,
        .min_integral = -1000.0,
        .max_output = 50000.0,
        .min_output = -50000.0
    };
    
    /*Instantiate pid object*/
    PID_t motor_pid;
    /*Initialize PID controller*/
    pid_init(&motor_pid, &default_params);

    /*Set reference*/
    pid_set_reference(&motor_pid, 1500);

    /*Set initial speed*/
    motor_speed(&motor0, 25000, CLOCKWISE);

    /*Enable motor*/
    motor_enable(&motor0);

    /*Initialize SysTick timer*/
    SysTick_init();

    /*Initialize time to 0*/
    uint32_t t0 = 0, deltaTime = 0;

    while(1)
    {

        t0 = SysTick_millis();      //Capture time
        int32_t ticks = motor_position(&motor0);    //Capture total ticks

        /*Get pid update*/
        float output = pid_update(&motor_pid, ticks, deltaTime);

        /*Check output*/
        uint32_t direction = output < 0 ? CLOCKWISE : COUNTER_CLOCKWISE;

        /*Update motor speed from PID output*/
        motor_speed(&motor0, output, direction);

        /*Display logger*/
        log_info("ticks=%i, output=%f", ticks,output);

        deltaTime = SysTick_millis() - t0;      //Capture time

    }
}

void HAL_assert(const char *module, const int line)
{
    while(1)
    {

    }
}
