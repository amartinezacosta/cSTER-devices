#Set variables
#TODO: Put them on the top cmake
#set(CSTER_DRIVERS_LIB_PATH ../cSTER-drivers/build/ports/tm4c1233h6pm)
#set(CSTER_DEVICE_TABLE_PATH ../cSTER-drivers/build/ports/tm4c123/devices/tm4c1233h6pm)

#Build library
add_library(cSTER_devices_ppm STATIC src/ppm.c)
target_include_directories(cSTER_devices_ppm PRIVATE 
        ${CSTER_DRIVERS_INCLUDE_PATH}
        include/
        )

#Build example executable
#add_executable(single_motor_example examples/single_motor_example.c)
#target_include_directories(single_motor_example PRIVATE 
#        ${CSTER_DRIVERS_INCLUDE_PATH} 
#        include/
#        )
#target_link_libraries(single_motor_example PRIVATE 
#        ${CSTER_DRIVERS_LIB_PATH}/cSTER_drivers_tm4c1233h6pm 
#        ${CSTER_DEVICE_TABLE_PATH}/devtable_robotic_arm_tm4c1233h6pm
#        )
