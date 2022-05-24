/**
 * @file motor.h
 * @authors Alejandro Martinez (mailto:amartinezacosta@miners.utep.edu)
 * @authors Jesus Minjares (mailto:jminjares4@miners.utep.edu)
 * @brief Motor device library
 * @version 0.1
 * @date 2022-05-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include <PWM_HAL.h>
#include <GPIO_HAL.h>

#define CLOCKWISE               0   /*!< Motor Clockwise */
#define COUNTER_CLOCKWISE       1   /*!< Motor Counter-Clockwise */

/******************************************************************
 * \struct motor_t motor.h 
 * \brief Motor object
 * 
 * ### Example
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.c
 * typedef struct{
 *      // Peripherals
 *      dev_t *pwm0;
 *      dev_t *pwm1;
 *      dev_t *gpio0;
 *      dev_t *gpio1;
 *      dev_t *gpio_sleep;
 *      // Encoder variables
 *      int32_t count;
 *      int32_t prev_count;
 *      int32_t delta_count;
 *      uint8_t state;
 *      uint32_t min_speed;
 * }motor_t;
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
typedef struct
{
    /*Peripherals*/
    dev_t *pwm0;
    dev_t *pwm1;
    dev_t *gpio0;
    dev_t *gpio1;
    dev_t *gpio_sleep;

    /*Encoder variables*/
    int32_t count;
    int32_t prev_count;
    int32_t delta_count;
    uint8_t state;
    uint32_t min_speed;
}motor_t;

void motor_ctor(motor_t * const me,
                dev_t *pwm0,
                dev_t *pwm1,
                dev_t *gpio0,
                dev_t *gpio1,
                dev_t *gpio_sleep);

void motor_enable(motor_t * const me);
void motor_disable(motor_t * const me);
void motor_set_min_speed(motor_t * const me, uint32_t min_speed);
void motor_speed(motor_t * const me,
                 uint32_t const speed,
                 uint32_t const direction);
int32_t motor_position(motor_t * const me);
int32_t motor_position_delta(motor_t * const me);

#endif
