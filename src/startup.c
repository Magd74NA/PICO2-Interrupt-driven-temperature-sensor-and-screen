/**
 * startup.c — implementation of the application initialisation layer.
 *
 * Bring each subsystem up in dependency order, bailing out early if anything
 * fails (main() hard_assert()s the return value). Add future init calls here.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "startup.h"

#include "board_led.h"
#include "pico/stdlib.h"

int startup_init(void) {
    // On-board LED driver (GPIO on plain Pico, CYW43 on Pico W).
    const int rc = board_led_init();
    if (rc != PICO_OK) {
        return rc;
    }

    // TODO: stdio_init_all(), sensors, comms, etc. go here as the project grows.

    return PICO_OK;
}
