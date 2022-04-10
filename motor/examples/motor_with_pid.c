#include <logger.h>
#include "motor.h"
#include "pid.h"
#include "SysTick_HAL.h"


int main(void)
{
    /*Find from device table*/
    dev_t *pwm0 = HAL_find_name("PWM_0");
    dev_t *pwm1 = HAL_find_name("PWM_1");
    dev_t *gpio0 = HAL_find_name("GPIO_0");
    dev_t *gpio1 = HAL_find_name("GPIO_1");
    dev_t *gpio_sleep = HAL_find_name("GPIO_2");

    /*Assert all pointers*/
    HAL_ASSERT_MODULE_NAME(pwm0 &&
                           pwm1 &&
                           gpio0 &&
                           gpio1 &&
                           gpio_sleep, "motor");

    /*Instantiate motor_t object*/
    motor_t motor0;
    motor_ctor(&motor0, pwm0, pwm1, gpio0, gpio1, gpio_sleep);

    /*Set default parameters for PID*/
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
    /*Instantiate pid object*/
    PID_t motor_pid;
    /*Initialize PID controller*/
    pid_init(&motor_pid, default_params);

    /*Set reference*/
    pid_set_reference(&motor_pid, motor0.count);

    /*Set initial speed*/
    motor_speed(&motor0, 25000, CLOCKWISE);

    /*Initialize SysTick timer*/
    SysTick_init();

    while(1)
    {
       
        uint32_t deltaTime = SysTick_millis();      //Capture time
        int32_t ticks = motor_position(&motor0);    //Capture total ticks
       
        /*Get pid update*/
        float output = pid_update(&motor_pid, ticks, deltaTime);
        /*Update motor speed from PID output*/
        motor_speed(&motor0, output, CLOCKWISE);

        /*Display logger*/
        log_info("ticks=%i, output=%f", ticks,output);
    }
}

void HAL_assert(const char *module, const int line)
{
    while(1)
    {

    }
}
