# Pico C SDK — Learning Resources & Guides

Curated tutorials and guides for Raspberry Pi Pico C/C++ SDK development.
All entries focus on the **C/C++ SDK** (not MicroPython) and were verified live.

---

## Official (the canon)

| Resource | Link |
|---|---|
| **Pico-series C/C++ SDK** — Doxygen API reference | https://rptl.io/pico-c-sdk |
| **Getting started with Pico-series** — onboarding + SWD debugging + picotool | https://rptl.io/pico-get-started |
| **pico-examples** — categorized working examples per peripheral ⭐ best teacher | https://github.com/raspberrypi/pico-examples |
| **RP2350 datasheet** — register-level hardware truth, PIO model | https://datasheets.raspberrypi.com/rp2350/rp2350-datasheet.pdf |
| **picotool** — USB flash/inspect tool | https://github.com/raspberrypi/picotool |

> The locally-installed SDK docs at `~/pico/pico-sdk/docs/` match your exact SDK version.

---

## Community tutorials

### 1. wisonye / embedded-tutorial-with-rp2040 ⭐ most in-depth
🔗 https://github.com/wisonye/embedded-tutorial-with-rp2040

A free, long-form "how it actually works under the hood" tutorial.

**Benefits:**
- **Teaches mechanism, not just API calls** — the standout. Explains how `main` actually gets called, how `printf` reaches USB/UART, how CMake builds your program, and writing the ARM startup file + linker script from scratch.
- **Pairs perfectly with bare-metal work** — if you want to understand the boot-to-main flow and startup code, this is the resource.
- Covers SPI and interrupts with working demos, plus Pico W WiFi/Bluetooth.
- **Best for:** understanding the *why* behind the SDK, going below the abstraction.

---

### 2. DeepBlueMbedded — Pico C/C++ SDK series ⭐ best topic-by-topic course
🔗 https://deepbluembedded.com/raspberry-pi-pico-w-sdk-c-programming-rp2040/

A structured multi-part course (landing page is the index).

**Benefits:**
- **Systematic per-peripheral coverage** — toolchain → project creation → GPIO → ADC → PWM → I2C → UART → timers → interrupts → DMA. Learn one peripheral at a time.
- **Consistent format** — schematics, full code, downloadable project per tutorial.
- **Explicitly C-SDK** — Arduino/MicroPython kept in separate tracks.
- **Best for:** methodically learning the whole peripheral set; your go-to per-topic reference.

---

### 3. Electrocredible — Pico category
🔗 https://electrocredible.com/category/raspberry-pi-pico/

Short, focused, practical how-tos.

**Benefits:**
- **Fast answers** — "I just want the working snippet for X" (external interrupts, ADC, I2C sensor wiring).
- **Copy-pasteable code** with clear wiring diagrams.
- **Best for:** quick lookup when you're mid-project and need a specific pattern fast.

---

### 4. SiliconWit — Embedded Programming (RPi Pico)
🔗 https://siliconwit.com/education/embedded-programming-rpi-pico/

A gentler, pedagogically-structured intro series.

**Benefits:**
- **Concepts first, hardware second** — timers, interrupts, and concurrency as embedded *concepts*, using the Pico as the vehicle.
- **Beginner-friendly** without being shallow.
- **Best for:** learning embedded fundamentals alongside the Pico.

---

### 5. Greg Chadwick — "Playing with the Pico" blog series
🔗 https://gregchadwick.co.uk/blog/playing-with-the-pico-pt2/ (pt2, pt4, …)

Written by an ex-ARM/Broadcom engineer.

**Benefits:**
- **Lowest-level writing available** — bit-banging, poking registers directly, understanding PIO and the boot process from first principles.
- **Expert perspective** — insight you won't find in tutorial farms.
- **Best for:** once you're past "make LED blink" and want to really understand the silicon.

---

### 6. DeepWiki — auto-generated source walkthroughs
🔗 https://deepwiki.com/raspberrypi/pico-sdk and https://deepwiki.com/raspberrypi/pico-examples

AI-generated explained topic pages from the actual repo source.

**Benefits:**
- **Annotated source tours** — explained topic pages (dedicated PIO walkthrough, DMA Controller deep dive, with code annotations).
- **Bridges the gap** between terse official Doxygen and a human explanation.
- **Best for:** when official docs are too terse and you want a guided tour of how the SDK *implements* something.

---

## Books

**RP2040 Assembly Language Programming** (Apress / O'Reilly)
- Covers startup, vector tables, and PIO in assembly.
- **Best for:** understanding the SDK's startup code at the instruction level; pairs with bare-metal work.

**Raspberry Pi Pico 2 W and RP2040 Programming** (Packt) — code: https://github.com/PacktPublishing/Raspberry-Pi-Pico-DIY-Workshop
- **Newer, RP2350 / Pico 2 aware** — most books predate the Pico 2.
- Project-oriented DIY format.

---

## Project-oriented guides

- **MQTT on Pico W (C SDK):** https://www.tomshardware.com/how-to/send-and-receive-data-raspberry-pi-pico-w-mqtt
- **IoT sensor → MQTT:** https://core-electronics.com.au/guides/getting-started-with-mqtt-on-raspberry-pi-pico-w-connect-to-the-internet-of-things/

**Best for:** seeing how all the pieces (WiFi + sensors + cloud) fit together in a real build.

---

## Quick recommendation

| Goal | Resource |
|---|---|
| Go deep under the hood | #1 wisonye |
| Learn a specific peripheral | #2 DeepBlueMbedded |
| Understand the silicon / PIO deeply | #5 Greg Chadwick |
| Quick snippet lookup | #3 Electrocredible |
| See the SDK source explained | #6 DeepWiki |
