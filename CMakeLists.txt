cmake_minimum_required(VERSION 3.10)

set(CSTER_DRIVERS_INCLUDE_PATH ../cSTER-drivers/include/)
set(CSTER_DRIVERS_TOOLCHAIN_PATH cSTER-drivers/cmake)

set(CMAKE_TOOLCHAIN_FILE ${CSTER_DRIVERS_TOOLCHAIN_PATH}/toolchain-arm-none-eabi.cmake)

project(cSTER-devices)

#cSTER drivers
add_subdirectory(cSTER-drivers/)

#Devices build
add_subdirectory(motor/)
add_subdirectory(ppm/)
add_subdirectory(servo/)
#add_subdirectory(wifi/)

add_library(cSTER_devices INTERFACE)
target_link_libraries(cSTER_devices INTERFACE 
    cSTER_devices_motor
    cSTER_devices_ppm
    #cSTER_devices_servo
    )

