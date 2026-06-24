/**
 * board_led.h — on-board LED abstraction.
 *
 * Hides the board-specific LED wiring so application code never has to branch
 * on board type. On a plain Pico the LED is a normal GPIO (PICO_DEFAULT_LED_PIN
 * is defined by the board header); on a Pico W / Pico 2 W it lives behind the
 * CYW43 wireless chip (CYW43_WL_GPIO_LED_PIN), which needs the cyw43_arch
 * driver initialised before it can be toggled. This module picks the right path
 * at compile time.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef BOARD_LED_H
#define BOARD_LED_H

#include <stdbool.h>

/**
 * Initialise the on-board LED. Call once before board_led_set().
 * @return 0 on success, non-zero on failure (e.g. cyw43 init error on Pico W).
 */
int board_led_init(void);

/**
 * Turn the on-board LED on or off.
 * @param on  true to light the LED, false to turn it off.
 */
void board_led_set(bool on);

/** Convenience: turn the on-board LED on. */
void board_led_on(void);

/** Convenience: turn the on-board LED off. */
void board_led_off(void);

#endif // BOARD_LED_H
