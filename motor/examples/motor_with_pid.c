#include <logger.h>
#include "motor.h"
#include "pid.h"


int main(void)
{
    dev_t *pwm0 = HAL_find_name("PWM_0");
    dev_t *pwm1 = HAL_find_name("PWM_1");
    dev_t *gpio0 = HAL_find_name("GPIO_0");
    dev_t *gpio1 = HAL_find_name("GPIO_1");
    dev_t *gpio_sleep = HAL_find_name("GPIO_2");

    HAL_ASSERT_MODULE_NAME(pwm0 &&
                           pwm1 &&
                           gpio0 &&
                           gpio1 &&
                           gpio_sleep, "motor");

    motor_t motor0;
    motor_ctor(&motor0, pwm0, pwm1, gpio0, gpio1, gpio_sleep);


    PID_Params_t default_params ={  .kp = 1.0,
                                    .ki = 0.0,
                                    .kd = 0.0,
                                    .error_max_threshold = 10.0,
                                    .error_min_threshold = -10.0,
                                    .max_integral = 1000.0,
                                    .min_integral = -1000.0,
                                    .max_output = 3000.0,
                                    .min_output = -3000.0
                                    };

    PID_t motor_pid;

    pid_init(&motor_pid, default_params);

    motor_speed(&motor0, 25000, CLOCKWISE);

    while(1)
    {
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
