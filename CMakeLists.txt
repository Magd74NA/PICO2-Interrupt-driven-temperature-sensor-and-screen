# Raspberry Pi Pico 2 W blink project, wired up for CLion.
#
# Build from CLI:
#   cmake -S . -B build --toolchain arm-none-eabi-gcc.cmake -G Ninja
#   cmake --build build
#
# Flash (board must be in BOOTSEL mode):
#   cmake --build build --target flash
#
# Layout:
#   src/        application sources (main.c, board_led.c)
#   include/    project headers (board_led.h)
#   Add new files to the pi_pico2w_SOURCES list below.

cmake_minimum_required(VERSION 3.13)

# --- Defaults: target the Pico 2 W (RP2350). Override with -D if needed. ---
# These must be set before pico_sdk_import.cmake is included.
if(NOT DEFINED PICO_BOARD)
    set(PICO_BOARD pico2_w CACHE STRING "Raspberry Pi Pico board definition")
endif()
if(NOT DEFINED PICO_PLATFORM)
    set(PICO_PLATFORM rp2350 CACHE STRING "Pico platform (rp2040 | rp2350)")
endif()
# Point at the local SDK checkout. Override with -DPICO_SDK_PATH=/path/to/sdk.
if(NOT DEFINED PICO_SDK_PATH)
    set(PICO_SDK_PATH /home/magd/pico/pico-sdk CACHE PATH "Path to the Raspberry Pi Pico SDK")
endif()

# Pull in the SDK (must come before project()).
include(${CMAKE_CURRENT_LIST_DIR}/pico_sdk_import.cmake)

project(pi_pico2w C CXX ASM)

# Default to C11/C++17 for everything; the SDK sources target C11.
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise the SDK (picks the arm-none-eabi toolchain for rp2350).
pico_sdk_init()

# --- The blink firmware ---
add_executable(pi_pico2w
    src/main.c
    src/startup.c
    src/board_led.c
)

set_target_properties(pi_pico2w PROPERTIES C_STANDARD 23 C_STANDARD_REQUIRED ON)
target_include_directories(pi_pico2w PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(pi_pico2w pico_stdlib)

# On boards whose LED is on the wireless chip (Pico 2 W), pull in the
# CYW43 driver so pico_led_init()/pico_set_led() actually light the LED.
if(PICO_CYW43_SUPPORTED)
    target_link_libraries(pi_pico2w pico_cyw43_arch_none)
endif()

# Generate pi_pico2w.bin / .hex / .uf2 / .dis / .map next to the executable.
pico_add_extra_outputs(pi_pico2w)

# --- `flash` target: load the UF2 onto the board via picotool -------------
# Requires a USB-enabled picotool (built with libusb) on the PATH, and the
# board held in BOOTSEL mode (hold BOOTSEL while powering on / resetting).
#
# picotool needs write access to the RP2350 USB device. On Linux that's granted
# by a udev rule; this project ships the rule at /etc/udev/rules.d/60-picotool.rules
# with MODE="0666" for the Raspberry Pi vendor IDs, so no sudo is needed.
find_program(PICOTOOL_EXE picotool)
if(PICOTOOL_EXE)
    add_custom_target(flash
        COMMAND ${PICOTOOL_EXE} load -x -v $<TARGET_FILE_DIR:pi_pico2w>/pi_pico2w.uf2
        DEPENDS pi_pico2w
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Flashing pi_pico2w.uf2 via picotool (board must be in BOOTSEL mode)"
        VERBATIM
    )
else()
    message(WARNING
        "picotool not found on PATH; the 'flash' target is disabled.\n"
        "Install a USB-enabled picotool (built against libusb-1.0) to enable flashing.")
endif()
