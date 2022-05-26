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

Motor are devices that are control by using `PWM` inorder to change its polarity or rotation direction. With the use of ***cSTER-drivers***, creating a Motor devices is straight forward as the API has peripheral support for `PWM`. The motor.h has support for the most common operations for motors. Table 1 will list the Motor API function calls that are available.

- Table 1
    |**Function**               |**Description**                      |
    |:---                       | :---                                |
    |motor_ctor()               | Create an instance of Motor object  |
    |motor_enable()             | Enable Motor                        |
    |motor_disable()            | Disable Motor                       |
    |motor_set_min_speed()      | Set motor minimum speed             |
    |motor_position()           | Get motor position                  |
    |motor_position_delta()     | Get previous motor                  |

@see \ref motor

### Quick Tutorial
This section will demostrate how to use motor.h to create simple **motor** application. The following code is a single **motor** moving at *50%* speed and rotating `clockwise`.
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

@see [Motor Guide](@ref resources/doc_pages/motor.md)

## Pulse-Position Modulation (PPM)  
### Description
**Pulse-Position Modulation (PPM)** is a modulation method that only makes every pulse in the carrier pulse sequence change with time but without changing the shape and amplitude of the pulse signal. With the use of ***cSTER-drivers***, creating a ppm devices is straight forward as it requires `Timer Capture` to reading its signals. ***cSTER-drivers*** has peripheral support for `Timer Capture`. The ppm.h has support to generate radio link. Table 2 will list the PPM API function calls that are available.

- Table 2
    |**Function**           |**Description**                    |
    |:---                   | :---                              |
    |ppm_ctor()             | Create an instance of PPM object  |
    |ppm_get_channels()     | Capture channels readings         |

@see \ref ppm

### Quick Tutorial
This section will demostrate how to use ppm.h to create simple **ppm radio link** application. The following code is reading a **ppm radio link** and display capture value through custom *logger*.
```c
#include <ppm.h>
#include <logger.h>
#include <SysTick_HAL.h>

int main(void)
{
    /*Find PPM device*/
    dev_t *capture = HAL_find_name("CAP_0");
    HAL_ASSERT_MODULE_NAME(capture, "main");

    /*Create an instance of PPM object*/
    ppm_t ppm;
    ppm_ctor(&ppm , capture, 8);

    uint32_t channels[8];
    while(1)
    {
        /*Read PPM channels*/
        ppm_get_channels(&ppm, channels);

        /*Log information*/
        log_info("%i,%i,%i,%i,%i,%i,%i,%i",
                 channels[0], channels[1],
                 channels[2], channels[3],
                 channels[4], channels[5],
                 channels[6], channels[7]);
        
        /*10 millisecond delay*/
        SysTick_delay(10);
    }
}
```

@see [PPM Guide](@ref resources/doc_pages/ppm.md)

## Servo
### Description
Servo are devices that are control by using `PWM` inorder to change its angle. With the use of ***cSTER-drivers***, creating a Servo devices is straight forward as the API has peripheral support for `PWM`. The servo.h has support for the most common operations for servos. Table 3 will list the Servo API function calls that are available.

- Table 3
    |**Function**          |**Description**                      |
    |:---                  | :---                                |
    |servo_ctor()          | Create an instance of servo object  |
    |servo_set_position()  | Set servo position                  |
    |servo_get_position()  | Get servo position                  |
    |servo_set_max()       | Set servo max value                 |
    |servo_set_min()       | Set servo max value                 |

@see \ref servo

### Quick Tutorial
This section will demostrate how to use servo.h to create simple **servo** application. The following code is a single **servo** moving from `5%` to `10%` duty cycle and vice-versa.
```c
#include <HAL.h>
#include <SysTick_HAL.h>
#include "servo.h"

int main(void)
{
    /*Find Servo device*/
    dev_t *pwm = HAL_find_name("PWM_0");
    HAL_ASSERT_MODULE_NAME(pwm, "main");
    
    /*Create an instance of Servo object*/
    servo_t servo;
    servo_ctor(&servo, pwm, 5000);

    while(1)
    {
        /*Set Servo posistion*/
        servo_set_position(&servo, 5000);
        SysTick_delay(2000);
        servo_set_position(&servo, 10000);
        SysTick_delay(2000);
    }
}
```
@see [Servo Guide](@ref resources/doc_pages/servo.md)

## WiFi
### Description
\todo Add Description Tutorial
@see \ref wifi

\todo Add Quick Tutorial
@see [WiFi Guide](@ref resources/doc_pages/wifi.md)
