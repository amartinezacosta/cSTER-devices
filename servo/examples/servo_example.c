/**
 * @dir servo
 * @brief This folder contains all files related to Servo
 * @details More details to be displayed on the folder's page.
 * 
 * @dir servo/example
 * @brief Servo device examples
 * @details More details to be displayed on the folder's page.
 * 
 * @file servo_example.c
 * @authors Alejandro Martinez (mailto:amartinezacosta@miners.utep.edu)
 * @authors Jesus Minjares (mailto:jminjares4@miners.utep.edu)
 * @brief Servo device example code
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <HAL.h>
#include <SysTick_HAL.h>
#include "servo.h"

int main(void)
{
    /*Find Servo device*/
    dev_t *pwm = HAL_find_name("PWM_0");
    HAL_ASSERT_MODULE_NAME(pwm, "main");
    
    /*Create an instance of Servo object*/
    servo_t servo;
    servo_ctor(&servo, pwm, 5000);

    while(1)
    {
        /*Set Servo posistion*/
        servo_set_position(&servo, 5000);
        SysTick_delay(2000);
        servo_set_position(&servo, 10000);
        SysTick_delay(2000);
    }
}

void HAL_assert(const char *module, const int line)
{
    while(1)
    {

    }
}
