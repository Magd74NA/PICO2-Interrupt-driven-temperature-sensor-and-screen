# Pico 2 W blink (CLion-ready)

Blink firmware for the Raspberry Pi **Pico 2 W**, built standalone against the
local pico-sdk and wired up to match your existing embedded-CLion workflow
(`arm-none-eabi-gcc.cmake` + "Debug-embedded" profile + `arm-none-eabi-gdb`).

## Layout

```
src/main.c               application entry point (the blink loop)
src/startup.c            application init layer (bring up all subsystems)
src/board_led.c          on-board LED driver implementation
include/startup.h        application init API
include/board_led.h      on-board LED driver API
docs/RESOURCES.md        curated C-SDK learning resources
CMakeLists.txt           project + `flash` target
arm-none-eabi-gcc.cmake  toolchain file for CLion's "Debug-embedded" profile
pico_sdk_import.cmake    locates the SDK at $PICO_SDK_PATH (default /home/magd/pico/pico-sdk)
```

The template uses a clean three-layer split: `main.c` (entry + loop) →
`startup` (init) → `board_led` (a hardware driver). Push board-specific
hardware details behind small driver APIs so `main()` and `startup_init()`
stay readable. Add new modules the same way (a `.c` in `src/`, a `.h` in
`include/`, append the `.c` to the `add_executable` list in `CMakeLists.txt`).

The build defaults to the **Pico 2 W** (`PICO_BOARD=pico2_w`, `PICO_PLATFORM=rp2350`).
Override either with `-D` at configure time to target a different board.

## The toolchain file

`arm-none-eabi-gcc.cmake` follows the same convention as your other (bare-metal)
projects, but for a Pico **SDK** project it just *delegates* to the SDK's own
Cortex-M33 GCC toolchain (`pico_arm_cortex_m33_gcc.cmake`) rather than
re-implementing it. That SDK toolchain:

- uses `arm-none-eabi-gcc` / `-g++` / `-objcopy` / `-objdump` — the same
  binaries your global "embedded" CLion toolchain points at;
- sets `-mcpu=cortex-m33 -mthumb -march=armv8-m.main+fp+dsp -mfloat-abi=softfp`;
- sets `CMAKE_SYSTEM_NAME=PICO` and the cross-compile find-root path.

Because `--toolchain` sets `CMAKE_TOOLCHAIN_FILE`, the SDK's
`pico_pre_load_toolchain.cmake` sees it already defined and skips its own
auto-selection — so there's no conflict, and the build uses `arm-none-eabi-gcc`.

## Command line

```bash
cmake -S . -B build --toolchain arm-none-eabi-gcc.cmake -G Ninja
cmake --build build

# Flash (board must be in BOOTSEL mode: hold BOOTSEL while powering on / reset)
cmake --build build --target flash
```

Produces `build/pi_pico2w.elf`, `.bin`, `.hex`, `.uf2`, and `.dis`.

## CLion

CLion already created the right profile (it's in `project.default.xml`):

- **"Debug-embedded"** — uses your global **embedded** toolchain
  (`arm-none-eabi-gcc` / `arm-none-eabi-gdb`) and passes
  `--toolchain arm-none-eabi-gcc.cmake`. Builds into `cmake-build-debug-embedded`.
  **This is the one to use.**

(There's also a plain "Debug" profile that builds into `cmake-build-debug`; it
works too because the SDK auto-selects the same `arm-none-eabi-gcc` toolchain,
but Debug-embedded is the consistent one with the rest of your projects.)

### Build & flash from CLion

- **Build:** pick the **`pi_pico2w`** target (CMake tool window) and Build.
- **Flash:** right-click the **`flash`** target → Run
  (board must be in BOOTSEL mode). The `flash` target runs
  `picotool load -x -v pi_pico2w.uf2`, loading the UF2 and booting it.

### One-click build+flash run config (optional)

Run → Edit Configurations → **+** → **Custom Build Application**:
- Target = a Custom Build Target that runs the `flash` target;
- Executable = `cmake-build-debug-embedded/pi_pico2w.elf` (so CLion's
  `arm-none-eabi-gdb` can attach over SWD later).

Running it builds and flashes in one click.

## Flashing

`flash` uses a **USB-enabled `picotool`** at `~/.local/bin/picotool` (built
against libusb-1.0). The picotool the SDK auto-downloads during a build is
compiled *without* USB support — that's why a separate one was installed.

```bash
cmake --build build --target flash      # or from CLion: Run the `flash` target
```

If `picotool` reports permission errors talking to the board, the udev rule for
the RP2350 isn't granting your user access. Quick workaround:
`sudo ~/.local/bin/picotool load -x -v build/pi_pico2w.uf2`.
Proper fix: install `~/.local/bin`'s picotool `udev/60-picotool.rules` into
`/etc/udev/rules.d/` (using `MODE="0666"` if you have no `plugdev` group) and
replug the board.

## Debugging (optional, needs a SWD probe)

`openocd` is installed and your "embedded" toolchain provides
`arm-none-eabi-gdb`, so you can step-debug `pi_pico2w.elf` in CLion via a
Picoprobe / Pi Debug Probe over SWD — same OpenOCD + embedded-GDB run
configuration pattern as your `pico-soil` / STM32 projects. Ask and I'll wire up
the debug-server config + OpenOCD interface file once you tell me which probe
you're using.

## Notes

- The SDK is referenced by absolute path (`/home/magd/pico/pico-sdk`). To
  relocate, set `PICO_SDK_PATH` in your environment or pass
  `-DPICO_SDK_PATH=/new/path` when configuring.
