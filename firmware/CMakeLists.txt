cmake_minimum_required(VERSION 3.13)

if(NOT DEFINED ENV{PICO_SDK_PATH} AND NOT DEFINED PICO_SDK_PATH)
    message(FATAL_ERROR "Set PICO_SDK_PATH (see firmware/README.md). Parser-only tests use Python: pytest from repo root.")
endif()

if(DEFINED PICO_SDK_PATH AND NOT DEFINED ENV{PICO_SDK_PATH})
    set(ENV{PICO_SDK_PATH} "${PICO_SDK_PATH}")
endif()

set(PICO_BOARD pico CACHE STRING "RP2040 Pico 264 kB")

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(axidraw_modern C CXX ASM)
pico_sdk_init()

add_executable(axidraw_modern
    src/main.c
    src/ebb_parser.c
)

target_include_directories(axidraw_modern PRIVATE include)

# pico_stdio_usb supplies TinyUSB CDC + descriptors. Do not link tinyusb_device:
# that sets LIB_TINYUSB_DEVICE and drops stdio_usb_descriptors.c (no iProduct).
target_link_libraries(axidraw_modern pico_stdlib)
pico_enable_stdio_usb(axidraw_modern 1)
pico_enable_stdio_uart(axidraw_modern 0)

# plotink.ebb_serial.findPort() matches description starting with EiBotBoard.
# VID stays Raspberry Pi 2E8A — not Microchip 04D8:FD92.
target_compile_definitions(axidraw_modern PRIVATE
    USBD_MANUFACTURER="axidraw-modern"
    USBD_PRODUCT="EiBotBoard"
)

pico_add_extra_outputs(axidraw_modern)
