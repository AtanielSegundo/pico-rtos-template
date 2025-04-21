# Generated CMake file for Pico W with FreeRTOS SMP port

cmake_minimum_required(VERSION 3.13)

# -----------------------------------------------------------------------------
# Project settings
# -----------------------------------------------------------------------------
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------------------------------------------------------
# Board selection and Pico SDK import
# -----------------------------------------------------------------------------
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if(EXISTS ${picoVscode})
    include(${picoVscode})
endif()

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(template C CXX ASM)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# -----------------------------------------------------------------------------
# FreeRTOS configuration include path
# -----------------------------------------------------------------------------
add_library(freertos_config INTERFACE)
target_include_directories(freertos_config INTERFACE
    ${CMAKE_SOURCE_DIR}/Config
)

# -----------------------------------------------------------------------------
# FreeRTOS-Kernel submodule and RP2040 SMP port
# -----------------------------------------------------------------------------
set(FREERTOS_KERNEL_PATH "${CMAKE_SOURCE_DIR}/FreeRTOS-Kernel" CACHE PATH "Path to FreeRTOS-Kernel submodule")
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# -----------------------------------------------------------------------------
# Application executable
# -----------------------------------------------------------------------------
add_executable(template
    template.c
)

# -----------------------------------------------------------------------------
# Link libraries
# -----------------------------------------------------------------------------
target_link_libraries(template
    pico_stdlib
    freertos_config
    hardware_gpio
    FreeRTOS-Kernel         # Core FreeRTOS kernel
    FreeRTOS-Kernel-Heap4   # Heap_4 allocator
)

# -----------------------------------------------------------------------------
# Enable/disable stdio
# -----------------------------------------------------------------------------
pico_enable_stdio_uart(template 0)
pico_enable_stdio_usb(template 1)

# -----------------------------------------------------------------------------
# Include project directory for headers
# -----------------------------------------------------------------------------
target_include_directories(template PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# -----------------------------------------------------------------------------
# Program metadata and extra outputs
# -----------------------------------------------------------------------------
pico_set_program_name(template "template")
pico_set_program_version(template "0.1")

pico_add_extra_outputs(template)
