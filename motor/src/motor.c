#include "motor.h"

void encoder_callback(void **args, uint32_t argc);

void motor_ctor(motor_t * const me,
                dev_t *pwm0,
                dev_t *pwm1,
                dev_t *gpio0,
                dev_t *gpio1,
                dev_t *gpio_sleep)
{
    me->pwm0 = pwm0;
    me->pwm1 = pwm1;
    me->gpio0 = gpio0;
    me->gpio1 = gpio1;
    me->gpio_sleep = gpio_sleep;

    PWM_open(me->pwm0, HAL_CONFIG_DEFAULT);
    PWM_open(me->pwm1, HAL_CONFIG_DEFAULT);

    GPIO_open(me->gpio0, HAL_CONFIG_DEFAULT);
    GPIO_open(me->gpio1, HAL_CONFIG_DEFAULT);
    GPIO_open(me->gpio_sleep, GPIO_MODE_OUTPUT);

    GPIO_ioctl(me->gpio0, HAL_IOCTL_EVENT_SET_CALLBACK, &encoder_callback);
    GPIO_ioctl(me->gpio1, HAL_IOCTL_EVENT_SET_CALLBACK, &encoder_callback);
    GPIO_ioctl(me->gpio0, HAL_IOCTL_EVENT_SET_ARGS, me);
    GPIO_ioctl(me->gpio1, HAL_IOCTL_EVENT_SET_ARGS, me);

    /*Initialize encoder variables*/
    me->count = 0;

    //uint8_t state = 0;
    //if(GPIO_read(me->gpio0)){ state |= 1; }
    //if(GPIO_read(me->gpio1)){ state |= 2; }

    //me->state = state;
}

void motor_enable(motor_t * const me)
{
    GPIO_write(me->gpio_sleep, GPIO_STATE_HIGH);
}

void motor_disable(motor_t * const me)
{
    GPIO_write(me->gpio_sleep, GPIO_STATE_LOW);
}

void motor_speed(motor_t * const me,
                 uint32_t const speed,
                 uint32_t const direction)
{
    if(direction == CLOCKWISE)
    {
        PWM_write(me->pwm0, speed);
        PWM_write(me->pwm1, 0);
    }
    else
    {
        PWM_write(me->pwm0, 0);
        PWM_write(me->pwm1, speed);
    }
}

void motor_stop(motor_t * const me)
{
    PWM_write(me->pwm0, 0);
    PWM_write(me->pwm1, 0);
}

int32_t motor_position(motor_t * const me)
{
    return me->count;
}

void encoder_callback(void **args, uint32_t argc)
{
    motor_t *me = (motor_t*)args[0];

    uint8_t input_0 = GPIO_read(me->gpio0);
    uint8_t input_1 = GPIO_read(me->gpio1);

    /*TODO: This is not the right way to read the encoders.
     * We are missing half of the pulses.
     */
    if(input_0)
    {
        if(input_1) me->count++;
        else        me->count--;
    }
    if(input_1)
    {
        if(input_0) me->count--;
        else        me->count++;
    }
}

