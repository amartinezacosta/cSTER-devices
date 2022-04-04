cmake_minimum_required()

set(CMAKE_TOOLCHAIN_FILE cSTER-drivers/toolchain-arm-none-eabi.cmake)

project(cSTER-devices)

#Devices build
add_subdirectory(motor/)
add_subdirectory(ppm/)
#add_subdirectory(wifi/)

#Devices build

