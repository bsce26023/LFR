# High-Speed Line Follower Robot (LFR)

An ultra-fast, high-performance autonomous Line Follower Robot powered by an STM32 microcontroller and custom-engineered hardware.

---

## Overview

### What It Does
This project is an autonomous high-speed mobile robot designed to detect, track, and navigate a high-contrast path on the ground at maximum velocity. It utilizes a precision optical sensor array to read surface reflections, processes the tracking data in real time via an onboard microcontroller, and dynamically modulates motor speeds through dedicated drivers to maintain stable path-following control even through sharp turns and complex curves.

### Why It Was Built
Traditional entry-level line followers built on basic microcontrollers often suffer from latency, sluggish motor response, and poor traction control. This project was engineered to push the boundaries of embedded control systems:
* **Performance Optimization:** Transitioning from basic 8-bit platforms to a robust 32-bit STM32 architecture for faster instruction cycles and precise PWM control.
* **Custom Hardware Integration:** Designing a dedicated, compact PCB to eliminate wiring clutter, reduce parasitic inductance, and ensure clean power distribution to high-current motors and sensor stages.
* **Engineering Rigor:** Serving as a practical testbed for closed-loop control algorithms, PCB fabrication techniques, and reliable firmware deployment workflows.

---

## Components

| Category | Component / Description | Qty |
| :--- | :--- | :--- |
| **Processing** | STM32 Microcontroller Board (e.g., STM32F103C8T6 "Blue Pill" or equivalent) | 1 |
| **Sensing** | Infrared (IR) Reflectance Sensor Array (analog/digital output) | 1 Set |
| **Actuation** | High-RPM DC Micro Gear Motors with wheels | 2 |
| **Motor Drive** | Dual-Channel Motor Driver (e.g., TB6612FNG or L298D) | 1 |
| **Power** | LiPo Battery (2S / 7.4V or suitable voltage rating) | 1 |
| **Hardware** | Custom Etched/Fabricated PCB Motherboard | 1 |
| **Hardware** | Spacers, mounting brackets, chassis frame, and wiring headers | - |

---

## Custom PCB

The custom printed circuit board integrates the microcontroller socket, motor driver, sensor headers, and power regulation onto a single optimized layout. 

* **Design Files:** Check the `PCB/` directory for schematic files, board layouts, and Gerber files.
* **Fabrication:** Designed for single-sided or double-sided fabrication (via chemical etching or professional manufacturing) with dedicated power planes to minimize noise interference between the high-current motor drivers and sensitive analog sensor inputs.

---

## Assembly & Firmware Guide

Because STM32 boards lack native USB bootloaders out-of-the-box like standard Arduino boards, flashing firmware requires a specific procedure using either an **ST-LINK V2 programmer** or the **built-in UART system memory bootloader**. 

### Step 1: Mechanical & Electrical Assembly
1. **Chassis & Motors:** Secure the DC gear motors to the mechanical chassis frame and attach the wheels.
2. **PCB Mounting:** Mount the fabricated PCB securely onto the chassis using standoffs.
3. **Wiring Connections:**
   * Connect the motor output leads from the gear motors to the motor driver output terminals (`M1`, `M2`).
   * Connect the IR sensor array to the designated analog/digital input header pins on the PCB.
   * Wire the power distribution, ensuring proper fusing and a stable common ground between the logic circuitry and motor drivers.

### Step 2: Setting Up the Development Environment
1. Install **Visual Studio Code** with the **PlatformIO IDE** extension (recommended for STM32 development) or **Arduino IDE** with the STMSS/STM32 Cores by STMicroelectronics installed via the Board Manager.
2. Clone or download this repository to your local machine.

### Step 3: Connecting the Programmer (ST-LINK V2 Method)
To flash code to an STM32 board, wire an external **ST-LINK V2 programmer** to the board's SWD pins:

| ST-LINK V2 Pin | STM32 Target Pin | Function |
| :--- | :--- | :--- |
| **3.3V** | **3.3V** | Power Supply |
| **GND** | **GND** | Common Ground |
| **SWDIO** | **PA13 (DIO)** | Serial Wire Data |
| **SWCLK** | **PA14 (CLK)** | Serial Wire Clock |

*Note: Ensure the target board is powered either via the ST-LINK's 3.3V pin (if current draw is low) or via an independent battery/bench supply.*

### Step 4: Uploading the Firmware
1. Open the project workspace in your IDE.
2. Verify that your `platformio.ini` or Arduino board settings match your exact STM32 part number (e.g., `stm32f103c8`).
3. Build/compile the project to check for syntax or dependency errors.
4. Initiate the upload command:
   * **In PlatformIO:** Click the **Upload** arrow icon (PlatformIO will automatically invoke OpenOCD and interface with your ST-LINK).
   * **In Arduino IDE:** Select **ST-LINK** under *Tools > Programmer*, then click **Upload**.
5. Once the upload finishes successfully, disconnect the programmer (or keep it connected for serial debugging via UART if configured), power cycle the robot, and place it on the test track.