/**
 * startup.h — application initialisation.
 *
 * A single place to bring up every board peripheral and application subsystem
 * before main() enters its loop. main() should call startup_init() once and
 * hard_assert() the result; add new subsystem init calls inside startup_init()
 * as the project grows, so main() stays a thin entry point.
 *
 * (This is an application-level "startup" layer, sitting above the SDK's own
 * crt0/reset handling. It is NOT the ARM vector-table / Reset_Handler startup
 * that bare-metal projects ship — the Pico SDK provides that in crt0.S.)
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef STARTUP_H
#define STARTUP_H

/**
 * Initialise all board peripherals and application subsystems.
 * Call exactly once at the top of main(), before the main loop.
 * @return PICO_OK on success, non-zero on failure.
 */
int startup_init(void);

#endif // STARTUP_H
