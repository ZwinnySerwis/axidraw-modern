cmake_minimum_required(VERSION 3.13)

if(NOT DEFINED ENV{PICO_SDK_PATH} AND NOT DEFINED PICO_SDK_PATH)
    message(FATAL_ERROR "Set PICO_SDK_PATH (see firmware/README.md). Parser-only tests use Python: pytest from repo root.")
endif()

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(axidraw_modern C CXX ASM)
pico_sdk_init()

add_executable(axidraw_modern
    src/main.c
    src/ebb_parser.c
)

target_include_directories(axidraw_modern PRIVATE include)
target_link_libraries(axidraw_modern pico_stdlib tinyusb_device tinyusb_board)
pico_enable_stdio_usb(axidraw_modern 1)
pico_enable_stdio_uart(axidraw_modern 0)
pico_add_extra_outputs(axidraw_modern)
