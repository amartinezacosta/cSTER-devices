#include "motor.h"

void encoder_callback(void **args, uint32_t argc);

/******************************************************************
 * \brief Motor constructor
 * 
 * Detailed description starts here 
 * @param me            pointer to Motor object
 * @param pwm0          pwm0 channel A
 * @param pwm1          pwm1 channel B
 * @param gpio0         encoder A
 * @param gpio1         encoder B
 * @param gpio_sleep    motor sleep
 * @return None
 *******************************************************************/
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
    me->prev_count = 0;
    me->count = 0;
    me->min_speed = 7500;
}

/******************************************************************
 * \brief Motor enable
 * 
 * Detailed description starts here 
 * @param me            pointer to Motor object
 * @return None
 *******************************************************************/
void motor_enable(motor_t * const me)
{
    GPIO_write(me->gpio_sleep, GPIO_STATE_HIGH);
}

/******************************************************************
 * \brief Motor disable
 * 
 * Detailed description starts here 
 * @param me            pointer to Motor object
 * @return None
 *******************************************************************/
void motor_disable(motor_t * const me)
{
    GPIO_write(me->gpio_sleep, GPIO_STATE_LOW);
}

/******************************************************************
 * \brief Motor speed
 * 
 * Detailed description starts here 
 * @param me            pointer to Motor object
 * @param speed         motor speed 
 * @param direction     motor direction
 * @return None
 *******************************************************************/
void motor_speed(motor_t * const me,
                 uint32_t const speed,
                 uint32_t const direction)
{
    if(speed < me->min_speed)
    {
        PWM_write(me->pwm0, 0);
        PWM_write(me->pwm1, 0);
        return;
    }

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

/******************************************************************
 * \brief Motor stop
 * 
 * Detailed description starts here 
 * @param me            pointer to Motor object
 * @return None
 *******************************************************************/
void motor_stop(motor_t * const me)
{
    PWM_write(me->pwm0, 0);
    PWM_write(me->pwm1, 0);
}

/******************************************************************
 * \brief Motor position
 * 
 * Detailed description starts here 
 * @param me            pointer to Motor object
 * @return int32_t      notor position
 *******************************************************************/
int32_t motor_position(motor_t * const me)
{
    return me->count;
}

/******************************************************************
 * \brief Motor position delta
 * 
 * Detailed description starts here 
 * @param me            pointer to Motor object
 * @return int32_t      motor position 
 *******************************************************************/
int32_t motor_position_delta(motor_t * const me)
{
    int32_t count = me->count;
    int32_t prev_count = me->prev_count;

    me->prev_count = me->count;

    return (count - prev_count);
}

void encoder_callback(void **args, uint32_t argc)
{
    motor_t *me = (motor_t*)args[0];

    uint8_t input_0 = GPIO_read(me->gpio0);
    uint8_t input_1 = GPIO_read(me->gpio1);

    /*TODO: This is not the right way to read the encoders.
     * We are missing half of the pulses.*/
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

    //me->delta_count = me->count - me->prev_count;
    //me->prev_count = me->count;
}

