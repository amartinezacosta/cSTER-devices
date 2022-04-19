#Build library
add_library(cSTER_devices_motor STATIC src/motor.c)
add_library(cSTER_devices_pid STATIC src/pid.c)

target_include_directories(cSTER_devices_motor PRIVATE 
        ${CSTER_DRIVERS_INCLUDE_PATH}
        include/
        )

target_include_directories(cSTER_devices_pid PRIVATE 
        ${CSTER_DRIVERS_INCLUDE_PATH}
        include/
)

#Build example executables
set(LINKER_SCRIPT_TM4C1233H6PM ${CMAKE_SOURCE_DIR}/cSTER-drivers/ports/tm4c123/linker_scripts/tm4c1233h6pm_minimal.ld)

#Single motor example
add_executable(single_motor_example examples/single_motor_example.c)
target_include_directories(single_motor_example PRIVATE 
        ${CSTER_DRIVERS_INCLUDE_PATH} 
        include/
        )

target_link_options(single_motor_example PRIVATE -T${LINKER_SCRIPT_TM4C1233H6PM})
target_link_libraries(single_motor_example PRIVATE
        devtable_robotic_arm_tm4c1233h6pm
        cSTER_drivers_tm4c1233h6pm
        devtable_robotic_arm_tm4c1233h6pm
        cSTER_drivers_tm4c1233h6pm
        cSTER_devices_motor
        )

#Multiple motors example
add_executable(mutiple_motor_example examples/multiple_motor_example.c)
target_include_directories(mutiple_motor_example PRIVATE 
        ${CSTER_DRIVERS_INCLUDE_PATH} 
        include/
        )

target_link_options(mutiple_motor_example PRIVATE -T${LINKER_SCRIPT_TM4C1233H6PM})
target_link_libraries(mutiple_motor_example PRIVATE
        devtable_robotic_arm_tm4c1233h6pm
        cSTER_drivers_tm4c1233h6pm
        devtable_robotic_arm_tm4c1233h6pm
        cSTER_drivers_tm4c1233h6pm
        cSTER_devices_motor
        )

#Motor with PID example
add_executable(motor_pid_example examples/motor_with_pid.c)
target_include_directories(motor_pid_example PRIVATE 
        ${CSTER_DRIVERS_INCLUDE_PATH} 
        include/
        )

target_link_options(motor_pid_example PRIVATE -T${LINKER_SCRIPT_TM4C1233H6PM})
target_link_libraries(motor_pid_example PRIVATE
        devtable_robotic_arm_tm4c1233h6pm
        cSTER_drivers_tm4c1233h6pm
        devtable_robotic_arm_tm4c1233h6pm
        cSTER_drivers_tm4c1233h6pm
        cSTER_devices_motor
        cSTER_devices_pid
        )

#PID experiment
add_executable(pid_experiment examples/pid_experiment.c)
target_include_directories(pid_experiment PRIVATE 
        ${CSTER_DRIVERS_INCLUDE_PATH} 
        include/
        )

target_link_options(pid_experiment PRIVATE -T${LINKER_SCRIPT_TM4C1233H6PM})
target_link_libraries(pid_experiment PRIVATE
        devtable_robotic_arm_tm4c1233h6pm
        cSTER_drivers_tm4c1233h6pm
        devtable_robotic_arm_tm4c1233h6pm
        cSTER_drivers_tm4c1233h6pm
        cSTER_devices_motor
        cSTER_devices_pid
        )

