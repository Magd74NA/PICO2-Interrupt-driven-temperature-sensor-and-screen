/**
 * main.c — blink the on-board LED.
 *
 * A minimal, idiomatic starting point: keep main() tiny and push board-specific
 * details into reusable modules (see board_led.h). Override the blink rate at
 * build time with -DLED_DELAY_MS=500.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "pico/stdlib.h"

#include "board_led.h"

#ifndef LED_DELAY_MS
#define LED_DELAY_MS 1000
#endif

int main(void) {
    hard_assert(board_led_init() == PICO_OK);

    while (true) {
        board_led_on();
        sleep_ms(LED_DELAY_MS);
        board_led_off();
        sleep_ms(LED_DELAY_MS);
    }
}
