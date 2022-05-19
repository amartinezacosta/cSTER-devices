cmake_minimum_required(VERSION 3.10)

#cSTER drivers
add_subdirectory(cSTER-drivers/)

#set(CSTER_DRIVERS_TOOLCHAIN_PATH cSTER-drivers/cmake)
#set(CMAKE_TOOLCHAIN_FILE ${CSTER_DRIVERS_TOOLCHAIN_PATH}/toolchain-arm-none-eabi.cmake)
set(CSTER_DRIVERS_INCLUDE_PATH ../cSTER-drivers/include/)

project(cSTER-devices)

#Devices build
#add_subdirectory(motor/)
#add_subdirectory(ppm/)
#add_subdirectory(servo/)
#add_subdirectory(wifi/)

set(MOTOR_SRC_FILES     motor/src/motor.c
                        motor/src/pid.c
                        )
set(PPM_SRC_FILES       ppm/src/ppm.c)
set(SERVO_SRC_FILES     servo/src/servo.c)
set(WIFI_SRC_FILES      wifi/src/wizfi360-pa/wizfi360.c
                        wifi/src/mqtt.c
                        )

set(MOTOR_INCLUDE_PATH   motor/include/)
set(PPM_INCLUDE_PATH     ppm/include/)
set(SERVO_INCLUDE_PATH   servo/include/)
set(WIFI_INCLUDE_PATH    wifi/include/)


add_library(cSTER_devices STATIC
        ${MOTOR_SRC_FILES}
        ${PPM_SRC_FILES}
        ${SERVO_SRC_FILES}
        ${WIFI_SRC_FILES}
        )        
#target_compile_definitions(cSTER_devices PRIVATE _DEV_T_DECLARED)
target_include_directories(cSTER_devices PRIVATE 
        ${CSTER_DRIVERS_INCLUDE_PATH}
        ${MOTOR_INCLUDE_PATH}
        ${PPM_INCLUDE_PATH}
        ${SERVO_INCLUDE_PATH}
        ${WIFI_INCLUDE_PATH}
        )
        
#Install cSTER devices
install(DIRECTORY ${MOTOR_INCLUDE_PATH} DESTINATION include/cSTER-devices)
install(DIRECTORY ${PPM_INCLUDE_PATH} DESTINATION include/cSTER-devices)
install(DIRECTORY ${SERVO_INCLUDE_PATH} DESTINATION include/cSTER-devices)
install(DIRECTORY ${WIFI_INCLUDE_PATH} DESTINATION include/cSTER-devices)
install(TARGETS cSTER_devices DESTINATION lib/)




