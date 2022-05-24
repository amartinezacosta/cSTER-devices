# Devices Documentation
<br />
<div align="center">
  <a href="https://github.com/amartinezacosta/cSTER-devices">
    <!-- ![](cSTER_logo.png) --> <!--Using image path in Doxyfile-->
 <img src="cSTER_logo.png" alt="Logo">
  </a>

  <h3 align="center">cSTER devices library for Cortex M4F microcontrollers</h3>

  <p align="center">
    Drivers for hardware devices using the cSTER drivers library
  </p>
</div>

## Motor

### Description

Motor are devices that are control by using H-bridge inorder to change its polarity or rotation direction. With the use of cSTER-drivers, creating a Motor devices is straight forward. The Motor.h has support for the most common operations for motors. Table 1 will list the Motor API function calls that are available.

- Table 1
    |**Function**               |**Description**                      |
    |:---                       | :---                                |
    |motor_ctor()               | Create an instance of Motor object  |
    |motor_enable()             | Enable Motor                        |
    |motor_disable()            | Disable Motor                       |
    |motor_set_min_speed()      | Set motor minimum speed             |
    |motor_position()           | Get motor position                  |
    |motor_position_delta()     | Get previous motor                  |

### Quick Tutorial
```c
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
    
    /*Assert buck converter device*/
    HAL_ASSERT_MODULE_NAME(enableSwReg, "main");
    
    /*Assert all motor devices*/
    HAL_ASSERT_MODULE_NAME(pwm0 &&
                           pwm1 &&
                           gpio0 &&
                           gpio1 &&
                           gpio_sleep, "motor");

    GPIO_open(enableSwReg, HAL_CONFIG_DEFAULT);
    /*Set GPIO high*/
    GPIO_write(enableSwReg, GPIO_STATE_HIGH);

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
```

## PPM
### Description

### Quick Tutorial


## Servo
### Description

### Quick Tutorial

## WiFi
### Description

\todo Add Quick Tutorial
