#include "servo.h"

void servo_ctor(servo_t * const me,
                dev_t * const pwm,
                uint32_t position)
{
    /*Open servo with default configuration*/
    PWM_open(pwm, HAL_CONFIG_DEFAULT);

    /*Servo frequency limited to 50Hz*/
    PWM_ioctl(pwm, HAL_IOCTL_PWM_SET_FREQUENCY, (uint32_t*)50);

    /*Set servo intial position*/
    if((position < 10000) &&
       (position > 5000))
    {
        PWM_write(pwm, position);
    }

    me->max = 10000;
    me->min = 5000;
    me->position = position;
    me->pwm = pwm;
}

void servo_set_position(servo_t * const me, uint32_t position)
{
    if((position < me->max) &&
       (position > me->min))
    {
        PWM_write(me->pwm, position);
        me->position = position;
    }
}

uint32_t servo_get_position(servo_t * const me)
{
    return me->position;
}

void servo_set_max(servo_t * const me, uint32_t max)
{
    me->max = max;
}

void servo_set_min(servo_t * const me, uint32_t min)
{
    me->min = min;
}





