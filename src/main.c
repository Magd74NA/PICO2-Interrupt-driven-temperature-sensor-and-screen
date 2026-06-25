/**
 * main.c — application entry point.
 *
 * Keeps main() tiny: initialise via the startup layer, then run the blink loop.
 * Blink rate is configurable at build time with -DLED_DELAY_MS=500.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

#include "board_led.h"
#include "startup.h"

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 1000
#endif

int main(void) {
    hard_assert(startup_init() == PICO_OK);

    while (true) {
        board_led_on();
        sleep_ms(LED_DELAY_MS);
        board_led_off();
        sleep_ms(LED_DELAY_MS);
    }
}
