#include <logger.h>
#include <SysTick_HAL.h>
#include <math.h>
#include <motor.h>
#include <pid.h>

#define DATA_POINTS 256

uint32_t time[DATA_POINTS];
int32_t encoder_output[DATA_POINTS];
uint32_t pwm_input[DATA_POINTS];


int main(void)
{
    /*Find from device table*/
    dev_t *pwm0 = HAL_find_name("PWM_0"); //motor 0 pwm
    dev_t *pwm1 = HAL_find_name("PWM_1");
    dev_t *pwm2 = HAL_find_name("PWM_2"); //motor 1 pwm
    dev_t *pwm3 = HAL_find_name("PWM_3");
    dev_t *gpio0 = HAL_find_name("GPIO_0"); //motor 0 encoders
    dev_t *gpio1 = HAL_find_name("GPIO_1");
    dev_t *gpio2 = HAL_find_name("GPIO_2"); //motor 1 encoders
    dev_t *gpio3 = HAL_find_name("GPIO_3");
    // motor 0/1 sleep
    dev_t *gpio_sleep0 = HAL_find_name("GPIO_8");

    dev_t *pwm4 = HAL_find_name("PWM_4"); //motor 2 pwm
    dev_t *pwm5 = HAL_find_name("PWM_5");
    dev_t *gpio4 = HAL_find_name("GPIO_4"); //motor 2 encoders
    dev_t *gpio5 = HAL_find_name("GPIO_5");
    // motor 2/3 sleep
    dev_t *gpio_sleep1 = HAL_find_name("GPIO_9");

    dev_t *enableSwReg = HAL_find_name("GPIO_13");

    HAL_ASSERT_MODULE_NAME(enableSwReg, "main");

    /*Assert all pointers*/
    HAL_ASSERT_MODULE_NAME(pwm0 &&
                           pwm1 &&
                           gpio0 &&
                           gpio1
                           , "motor0");

    HAL_ASSERT_MODULE_NAME(pwm2 &&
                           pwm3 &&
                           gpio2 &&
                           gpio3
                           , "motor1");

    HAL_ASSERT_MODULE_NAME(pwm4 &&
                           pwm5 &&
                           gpio4 &&
                           gpio5
                           , "motor2");

    HAL_ASSERT_MODULE_NAME(gpio_sleep0 && gpio_sleep1, "gpio_sleep");


    GPIO_open(enableSwReg, HAL_CONFIG_DEFAULT);
    GPIO_write(enableSwReg, GPIO_STATE_HIGH);

    /*Instantiate motor_t object*/
    motor_t motor0;
    motor_ctor(&motor0, pwm0, pwm1, gpio0, gpio1, gpio_sleep0);
    /*Instantiate motor_t object*/
    motor_t motor1;
    motor_ctor(&motor1, pwm2, pwm3, gpio2, gpio3, gpio_sleep0);
    /*Instantiate motor_t object*/
    motor_t motor2;
    motor_ctor(&motor2, pwm4, pwm5, gpio4, gpio5, gpio_sleep1);

    /*Set default parameters for PID*/
    PID_params_t default_params =
    {
        .kp = 25.0,
        .ki = 0.1,
        .kd = 0.0,
        .error_max_threshold = 10.0,
        .error_min_threshold = -10.0,
        .max_integral = 25000.0,
        .min_integral = -25000.0,
        .max_output = 40000.0,
        .min_output = -40000.0
    };

    /*Instantiate pid object*/
    PID_t motor_pid;
    /*Initialize PID controller*/
    pid_init(&motor_pid, &default_params);

    /*Set reference*/
    pid_set_reference(&motor_pid, 2660);
    pid_update(&motor_pid, 0.0, 0.0);

    /*Enable motors*/
    motor_enable(&motor0);
    motor_enable(&motor2);

    /*Initialize time to 0*/
    uint32_t t0 = 0.0;
    uint32_t dt = 0.0;
    uint32_t t = 0;
    uint32_t index = 0;

    log_info("Starting experiment");

    /*Perform experiment until set point has been reached*/
    while(!pid_reached(&motor_pid) && (t < 5000))
    {
        t0 = SysTick_millis();

        /*Motor position and PID update*/
        int32_t ticks = motor_position(&motor0);
        float output = pid_update(&motor_pid, (float)ticks, 0.03);

        /*Motor direction*/
        uint32_t direction = output < 0 ? CLOCKWISE : COUNTER_CLOCKWISE;
        uint32_t pwm = (uint32_t)fabs(output);

        motor_speed(&motor0, (uint32_t)fabs(output), direction);
        motor_speed(&motor1, (uint32_t)fabs(output), direction);
        motor_speed(&motor2, (uint32_t)fabs(output), direction);

        /*Save data for logging*/
        if(index < DATA_POINTS)
        {
            /*Dave data*/
            time[index] = t;
            pwm_input[index] = pwm;
            encoder_output[index] = ticks;

            /*Increment data index*/
            index++;
        }

        SysTick_delay(30);
        dt = SysTick_millis() - t0;
        t += dt;
    }

    motor_speed(&motor0, 0, 0);
    motor_speed(&motor1, 0, 0);
    motor_speed(&motor2, 0, 0);


    /*Experiment done, dump all data to serial console*/
    for(uint32_t i = 0; i < index; i++)
    {
        log_raw("%i,%i,%i", i, pwm_input[i], encoder_output[i]);
    }

    while(1)
    {

    }
}

void HAL_assert(const char *module, const int line)
{
    while(1)
    {

    }
}
