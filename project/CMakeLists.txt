cmake_minimum_required(VERSION 4.0)
project(stm32_test_project C)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linker/STM32F446RE_FLASH.ld)

include(cmake/arm-none-eabi.cmake)

add_executable(${PROJECT_NAME}.elf
    Core/Src/main.c
    Core/Src/system_stm32f4xx.c
    startup/startup_stm32f446xx.s
)

target_include_directories(${PROJECT_NAME}.elf PRIVATE
    Core/Inc
    ../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Inc
    ../STM32CubeF4/Drivers/CMSIS/Include
    ../STM32CubeF4/Drivers/CMSIS/Device/ST/STM32F4xx/Include
)

target_compile_options(${PROJECT_NAME}.elf PRIVATE -Wall -Wextra -fdiagnostics-color=always)

file(GLOB HAL_SRC
    ../STM32CubeF4/Drivers/STM32F4xx_HAL_Driver/Src/*.c
)

target_sources(${PROJECT_NAME}.elf PRIVATE ${HAL_SRC})

target_compile_definitions(${PROJECT_NAME}.elf PRIVATE
    STM32F446xx
    USE_HAL_DRIVER
)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE} ${PROJECT_NAME}.elf
)
