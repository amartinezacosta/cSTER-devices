#ifndef MOTOR_H_
#define MOTOR_H_

#include <PWM_HAL.h>
#include <GPIO_HAL.h>

#define CLOCKWISE               0
#define COUNTER_CLOCKWISE       1

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
}motor_t;

void motor_ctor(motor_t * const me,
                dev_t *pwm0,
                dev_t *pwm1,
                dev_t *gpio0,
                dev_t *gpio1,
                dev_t *gpio_sleep);

void motor_enable(motor_t * const me);
void motor_disable(motor_t * const me);
void motor_speed(motor_t * const me,
                 uint32_t const speed,
                 uint32_t const direction);
int32_t motor_position(motor_t * const me);
int32_t motor_position_delta(motor_t * const me);

#endif
