cmake_minimum_required(VERSION 3.10)

set(CSTER_DRIVERS_INCLUDE_PATH ../cSTER-drivers/include/)
set(CSTER_DRIVERS_TOOLCHAIN_PATH cSTER-drivers/cmake)

set(CMAKE_TOOLCHAIN_FILE ${CSTER_DRIVERS_TOOLCHAIN_PATH}/toolchain-arm-none-eabi.cmake)

project(cSTER-devices)

#Devices build
add_subdirectory(motor/)
add_subdirectory(ppm/)
#add_subdirectory(wifi/)

#Devices build

