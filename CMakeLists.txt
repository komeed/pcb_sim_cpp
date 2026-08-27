cmake_minimum_required(VERSION 3.31)
project(pcb_sim_cpp)

set(CMAKE_CXX_STANDARD 20)


add_executable(pcb_sim_cpp main.cpp
        mcu/nrf52840/nrf52840.h
        mcu/nrf52840/nrf52840.cpp
        elf/elf32.h
        global_vars.h
        utils/errorhandler.cpp
        utils/errorhandler.h
        mcu/nrf52840/nrf52840_registers.h
        components/pin.h
        components/component.h
        components/led.h
        mcu/mcu.h
        mcu/mcu.cpp
        components/pin.cpp
        components/pin.h
        components/component.cpp
        components/peripheral.cpp
        components/peripheral.h
        mcu/nrf52840/peripherals/nrf52840_gpio.cpp
        mcu/nrf52840/peripherals/nrf52840_gpio.h
        components/resistor.h
        components/capacitor.h
)

target_include_directories(pcb_sim_cpp PRIVATE
        /opt/homebrew/include
)

target_include_directories(pcb_sim_cpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_directories(pcb_sim_cpp PRIVATE
        /opt/homebrew/lib
)

target_link_libraries(pcb_sim_cpp
        unicorn
)