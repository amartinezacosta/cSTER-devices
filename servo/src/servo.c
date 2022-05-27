/**
 * @dir servo/src
 * @brief Servo device source code
 * @details More details to be displayed on the folder's page.
 * 
 * @file servo.c
 * @authors Alejandro Martinez (mailto:amartinezacosta@miners.utep.edu)
 * @authors Jesus Minjares (mailto:jminjares4@miners.utep.edu)
 * @brief Servo device source code
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "servo.h"

/******************************************************************
 * \brief Servo constructor
 * 
 * Detailed description starts here 
 * @param me            pointer to Servo object
 * @param pwm           pwm device
 * @param position      servo position
 * @return None
 *******************************************************************/
void servo_ctor(servo_t * const me,
                dev_t * const pwm,
                uint32_t position)
{
    /*Open servo with default configuration*/
    PWM_open(pwm, HAL_CONFIG_DEFAULT);

    /*Servo frequency limited to 50Hz*/
    // PWM_ioctl(pwm, HAL_IOCTL_PWM_SET_FREQUENCY, (uint32_t*)50);

    /*Set servo intial position*/
    if((position <= 100000) &&
       (position >= 50000))
    {
        PWM_write(pwm, position);
    }

    me->max = 100000;
    me->min = 50000;
    me->position = position;
    me->pwm = pwm;
}

/******************************************************************
 * \brief Servo set position
 * 
 * Detailed description starts here 
 * @param me            pointer to Servo object
 * @param position      servo position
 * @return None
 *******************************************************************/
void servo_set_position(servo_t * const me, uint32_t position)
{
    if((position <= me->max) &&
       (position >= me->min))
    {
        PWM_write(me->pwm, position);
        me->position = position;
    }
}

/******************************************************************
 * \brief Servo get position
 * 
 * Detailed description starts here 
 * @param me            pointer to Servo object
 * @return uint32_t     servo position
 *******************************************************************/
uint32_t servo_get_position(servo_t * const me)
{
    return me->position;
}

/******************************************************************
 * \brief Servo set max
 * 
 * Detailed description starts here 
 * @param me            pointer to Servo object
 * @param max           max value
 * @return None         
 *******************************************************************/
void servo_set_max(servo_t * const me, uint32_t max)
{
    me->max = max;
}

/******************************************************************
 * \brief Servo set min
 * 
 * Detailed description starts here 
 * @param me            pointer to Servo object
 * @param max           min value
 * @return None         
 *******************************************************************/
void servo_set_min(servo_t * const me, uint32_t min)
{
    me->min = min;
}





