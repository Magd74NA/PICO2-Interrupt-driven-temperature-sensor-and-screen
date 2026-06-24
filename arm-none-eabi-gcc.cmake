# arm-none-eabi-gcc.cmake — CMake toolchain file for CLion's "Debug-embedded"
# profile on this Pico 2 W (RP2350) project.
#
# Your other (bare-metal) projects ship a hand-written toolchain file here. For
# a Pico *SDK* project the SDK already maintains the correct, up-to-date GCC
# toolchain setup for the Cortex-M33, so rather than duplicate it (and risk
# drifting from the SDK), this file simply delegates to the SDK's own
# `pico_arm_cortex_m33_gcc.cmake`. That toolchain:
#   - uses arm-none-eabi-gcc / -g++ / -objcopy / -objdump (the same binaries
#     your "embedded" CLion toolchain points at)
#   - sets -mcpu=cortex-m33 -mthumb -march=armv8-m.main+fp+dsp -mfloat-abi=softfp
#   - sets CMAKE_SYSTEM_NAME=PICO and the cross-compile find root path
#
# Because CMAKE_TOOLCHAIN_FILE is set (via CLion's `--toolchain
# arm-none-eabi-gcc.cmake`), the SDK's pico_pre_load_toolchain.cmake sees it
# already defined and skips its own auto-selection — so there's no conflict.
#
# Consumed by the CLion "Debug-embedded" CMake profile via:
#     --toolchain arm-none-eabi-gcc.cmake

# Resolve PICO_SDK_PATH the same way pico_sdk_import.cmake does. The toolchain
# file runs very early (before project()), so prefer the environment variable
# (always visible); fall back to the local checkout path.
if(NOT DEFINED PICO_SDK_PATH)
    if(DEFINED ENV{PICO_SDK_PATH})
        set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
    else()
        set(PICO_SDK_PATH /home/magd/pico/pico-sdk)
    endif()
endif()

include(${PICO_SDK_PATH}/cmake/preload/toolchains/pico_arm_cortex_m33_gcc.cmake)
