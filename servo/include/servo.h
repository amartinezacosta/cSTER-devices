#ifndef SERVO_H_
#define SERVO_H_

#include <PWM_HAL.h>

/******************************************************************
 * \struct servo_t servo.h 
 * \brief Servo object
 * 
 * ### Example
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.c
 * typedef struct{
 *      dev_t *pwm;
 *      uint32_t max;
 *      uint32_t min;
 *      uint32_t position;
 * }servo_t;
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *******************************************************************/
typedef struct
{
    dev_t *pwm;
    uint32_t max;
    uint32_t min;
    uint32_t position;
}servo_t;

void servo_ctor(servo_t * const me,
                dev_t * const pwm,
                uint32_t position);
void servo_set_position(servo_t * const me,uint32_t value);
uint32_t servo_get_position(servo_t * const me);
void servo_set_max(servo_t * const me, uint32_t max);
void servo_set_min(servo_t * const me, uint32_t min);

#endif
