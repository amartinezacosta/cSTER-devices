#include <logger.h>
#include <GPIO_HAL.h>
#include "motor.h"

int main(void)
{
    /*Find all devices from device table*/
    dev_t *pwm00 = HAL_find_name("PWM_0");
    dev_t *pwm01 = HAL_find_name("PWM_1");
    dev_t *gpio00 = HAL_find_name("GPIO_0");
    dev_t *gpio01 = HAL_find_name("GPIO_1");
    dev_t *gpio0_sleep = HAL_find_name("GPIO_8");
    
    /*Find all devices from device table*/
    dev_t *pwm10 = HAL_find_name("PWM_2");
    dev_t *pwm11 = HAL_find_name("PWM_3");
    dev_t *gpio10 = HAL_find_name("GPIO_2");
    dev_t *gpio11 = HAL_find_name("GPIO_3");
    dev_t *gpio1_sleep = HAL_find_name("GPIO_8");

    
    /*Find all devices from device table*/
    dev_t *pwm20 = HAL_find_name("PWM_4");
    dev_t *pwm21 = HAL_find_name("PWM_5");
    dev_t *gpio20 = HAL_find_name("GPIO_4");
    dev_t *gpio21 = HAL_find_name("GPIO_5");
    dev_t *gpio2_sleep = HAL_find_name("GPIO_9");

    /*Enable buck converter*/
    dev_t *enableSwReg = HAL_find_name("GPIO_13");
    
    /*Assert devices motor 0*/
    HAL_ASSERT_MODULE_NAME(pwm00 &&
                           pwm01 &&
                           gpio00 &&
                           gpio01 &&
                           gpio0_sleep, "main");
                           
    /*Assert devices motor 1*/
    HAL_ASSERT_MODULE_NAME(pwm10 &&
                           pwm11 &&
                           gpio10 &&
                           gpio11 &&
                           gpio1_sleep, "main");
                           
    /*Assert devices motor 2*/
    HAL_ASSERT_MODULE_NAME(pwm20 &&
                           pwm21 &&
                           gpio20 &&
                           gpio21 &&
                           gpio2_sleep, "main");
                           
    /*Assert devices buck regulator*/
    HAL_ASSERT_MODULE_NAME(enableSwReg, "main");
    
    /*Create motor objects*/
    motor_t motor0, motor1, motor2;
    motor_ctor(&motor0, pwm00, pwm01, gpio00, gpio01, gpio0_sleep);
    motor_ctor(&motor1, pwm10, pwm11, gpio10, gpio11, gpio0_sleep);
    motor_ctor(&motor2, pwm20, pwm21, gpio20, gpio21, gpio1_sleep);
    
    /*Set motor speed*/
    motor_speed(&motor0, 25000, CLOCKWISE);
    motor_speed(&motor1, 25000, COUNTER_CLOCKWISE);
    motor_speed(&motor2, 25000, CLOCKWISE);
    
    motor_enable(&motor0);
    motor_enable(&motor1);
    motor_enable(&motor2);
    
    while(1)
    {
        int32_t ticks0 = motor_position(&motor0);
        int32_t ticks1 = motor_position(&motor1);
        int32_t ticks2 = motor_position(&motor2);
        
        log_info("ticks0 = %i, ticks1 = %i, ticks2 = %i\r\n");          
    }      
}

void HAL_assert(const char *module, const int line)
{
    while(1)
    {
        
    }
}
