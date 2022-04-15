#include <logger.h>
#include "motor.h"
#include <GPIO_HAL.h>
int main(void)
{
    /*Find all devices from device table*/
    dev_t *pwm0 = HAL_find_name("PWM_0");
    dev_t *pwm1 = HAL_find_name("PWM_1");
    dev_t *gpio0 = HAL_find_name("GPIO_0");
    dev_t *gpio1 = HAL_find_name("GPIO_1");
    dev_t *gpio_sleep = HAL_find_name("GPIO_8");

    /*Enable buck converter*/
    dev_t *enableSwReg = HAL_find_name("GPIO_13");
    GPIO_open(enableSwReg, HAL_CONFIG_DEFAULT);
    /*Set GPIO high*/
    GPIO_write(enableSwReg, GPIO_STATE_HIGH);
    /*Assert to main*/
    HAL_ASSERT_MODULE_NAME(enableSwReg, "main");


    /*Assert all motor devices*/
    HAL_ASSERT_MODULE_NAME(pwm0 &&
                           pwm1 &&
                           gpio0 &&
                           gpio1 &&
                           gpio_sleep, "motor");

    /*Motor setup*/
    motor_t motor0;

    /*Create an instance of motor*/
    motor_ctor(&motor0, pwm0, pwm1, gpio0, gpio1, gpio_sleep);

    /*Set motor speed to rotate clockwise*/
    motor_speed(&motor0, 25000, CLOCKWISE);

    /*Enable motor*/
    motor_enable(&motor0);
    while(1)
    {
        /*Display total ticks*/
        int32_t ticks = motor_position(&motor0);
        log_info("ticks=%i", ticks);
    }
}

void HAL_assert(const char *module, const int line)
{
    while(1)
    {

    }
}
