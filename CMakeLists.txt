cmake_minimum_required(VERSION 3.20)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pico-freertos-starter C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

add_library(freertos_config INTERFACE)
# The include path should be set to the directory where you have FreeRTOSConfig.h
target_include_directories(freertos_config SYSTEM INTERFACE include)
target_compile_definitions(freertos_config INTERFACE projCOVERAGE_TEST=0)
set(FREERTOS_KERNEL_PATH ${CMAKE_SOURCE_DIR}/FreeRTOS)
include(FreeRTOS_Kernel_Import.cmake)

add_executable(pico-freertos-starter
    main.c)

pico_set_program_name(pico-freertos-starter "pico-freertos-starter")
pico_set_program_version(pico-freertos-starter "0.1")

pico_enable_stdio_uart(pico-freertos-starter 0)
pico_enable_stdio_usb(pico-freertos-starter 1)

target_include_directories(pico-freertos-starter PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(pico-freertos-starter
    pico_stdlib
    hardware_timer
    pico_unique_id
    pico_multicore
    FreeRTOS-Kernel
    FreeRTOS-Kernel-Heap4)

pico_add_extra_outputs(pico-freertos-starter)

