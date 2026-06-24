/**
 * board_led.c — implementation of the on-board LED abstraction.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "board_led.h"

#include "pico/stdlib.h"

// Pico W devices drive the user LED from the wireless chip instead of a MCU
// GPIO. When the active board header is for a Pico W, the SDK defines
// CYW43_WL_GPIO_LED_PIN and we must go through pico_cyw43_arch to reach it.
#ifdef CYW43_WL_GPIO_LED_PIN
#include "pico/cyw43_arch.h"
#endif

int board_led_init(void) {
#if defined(PICO_DEFAULT_LED_PIN)
    // Plain Pico: the LED is a normal GPIO.
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    return PICO_OK;
#elif defined(CYW43_WL_GPIO_LED_PIN)
    // Pico W: bring up the CYW43 driver so we can poke its GPIOs.
    return cyw43_arch_init();
#else
#error "No on-board LED configured for this board (PICO_DEFAULT_LED_PIN / CYW43_WL_GPIO_LED_PIN both undefined)."
#endif
}

void board_led_set(bool on) {
#if defined(PICO_DEFAULT_LED_PIN)
    gpio_put(PICO_DEFAULT_LED_PIN, on);
#elif defined(CYW43_WL_GPIO_LED_PIN)
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on);
#endif
}

void board_led_on(void) {
    board_led_set(true);
}

void board_led_off(void) {
    board_led_set(false);
}
