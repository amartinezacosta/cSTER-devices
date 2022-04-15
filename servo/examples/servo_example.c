#include <HAL.h>
#include <SysTick_HAL.h>
#include "servo.h"

int main(void)
{
    dev_t *pwm = HAL_find_name("PWM_0");
    HAL_ASSERT_MODULE_NAME(pwm, "main");

    servo_t servo;
    servo_ctor(&servo, pwm, 5000);

    while(1)
    {
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
