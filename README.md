# Autonomous Line Following Robot

I designed a LFR from scratch including the PCBs for main board and a custom sensor array. I designed this because I saw a friend of mine going into robotics competetions, so I also wanted to participate in them but I didn't have a robot that I could take to those competetions, so I finally built one myself. I chose STM32 because in some of those events there is a requirement that your robot should not have wireless connectivity, so the first thing that came into my mind was arduino uno but it is very slow and basic compared to other microcontrollers available on market then after some research I had two options Raspberry Pi Pico RP2040 or a STM32 Black Pill. raspberry pi pico had only 3 analog pins so I went with STM32.

To View the 3D assembly -->  [Assembly](https://cad.onshape.com/documents/d45a99fa843b34be3d8e85fd/w/9a64eb3e4a0355d274d4a744/e/07efc429ec569cf6f0da1301?renderMode=0&uiState=6a73ae4ff920c2919cbadd91)



||||
| :---: | :---: | :---: |
| ![Top_view](3D/Images/5.JPG) | ![Corner_View_1](3D/Images/7.JPG) | ![Corner_View_2](3D/Images/8.JPG) |


# Components

I've decided the components based on affordability, speed, availability and ease of use.
Starting with the micro controller I've selected **STM 32 BlackPill** and for motors I've selected **3000rpm 6v N20 motors with encoders** for fast speed  to drive these motors I've chosen **TB6612FNG motor driver** because it has low voltage drop and also it is way lighter than L298N. I've decided to use a 2S Li-Po battery which is about 7.4v which can power the motors with ease and to power STM32 I'd use a step down buck converter to convert these 7.4v into 5v so we don't damage the STM32 to charge the battery I'd use a 2S charger and for the sensors I've designed a custom sensor array.

##  PCB and Connections

To talk about the connections, I'd Start with the Power connections. The battery provides 7.4v which goes to VMOT pin of motor driver and buck converter. the buck converter then outputs 5v which goes to VSYS on Pico. Now we have 3 voltages. i.e. 7.4v, 5v and 3.3v. now the 3.3v goes to VCC and STBY pin of TB6612FNG and VCC pin on Sensor Array. 
Now lets talk about the Data and Logic Signals. The GPIO pins from 0 to 18 will be connected to sensor array and GPIO pins 19,20, 21, 22, 26, 27 will be connected to PWMA, AIN1, AIN2, PWMB, BIN1 and BIN2 respectively.
At the end the AO1,  AO2 and BO1, BO2 will be connected to left and right motors respectively.
[![Schematics](Main%20Board/Images/Schematics.JPG)]

|Schematics|Tracks|
| :---: | :---: |
| ![3D](Main%20Board/Images/3D_1.JPG) | ![Tracks](Main%20Board//Images/Tracks.JPG) |




## Custom Built Sensor Array

I designed the schematics for the sensor array, it is the working principle is inspired from the QTR-16RC sensor array. I designed this because traditional sensors and sensor arrays look too uncool, so I had to design something that looked aesthetic and visually pleasing.

|Schematics|Tracks|
| :---: | :---: |
| ![schemetics](Custom%20Sensor%20Array/Images/Schematics.JPG) | ![Tracks](Custom%20Sensor%20Array/Images/Tracks.JPG) |

![3D](Custom%20Sensor%20Array/Images/3D.JPG)

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


# Bill of Materials (BOM)

| Name | Purpose | Quantity | Total Cost (USD) | Link | Distributor |
| --- | --- | --- | --- | --- | --- |
| PCB | PCB | 2 | 17 | https://cart.jlcpcb.com/shopcart/cart/ | JLCPCB |
| Mounting Brackets | Mounting motors | 1 | 3 | https://a.aliexpress.com/_c41oltrB | AliExpress |
| N20 Wheels | Wheels for Motors | 4 | 10 | https://a.aliexpress.com/_c3mDdjNx | Ali Express |
| Caster Wheels | Caster wheels | 2 | 4 | https://a.aliexpress.com/_c2yFCmMd | AliExpress |
| Slide Switch | Power Switch | 1 | 2 | https://a.aliexpress.com/_c3g6KmzX | AliExpress |
| TB6612FNG | Motor Driver | 1 | 4 | https://a.aliexpress.com/_c3bzgEgz | AliExpress |
| N20 Motors | Motors with Encoders | 4 | 25 | https://a.aliexpress.com/_c39Rykzn | AliExpress |
| Capacitor | Capacitance | 1 | 3 | https://a.aliexpress.com/_c3Ig4r1X | Aliexpress |
| Resistors | Resistance | 2 | 5 | https://a.aliexpress.com/_c3G1MsVL | Aliexpress |
| Limit switch | Bump sensor | 1 | 2.5 | https://a.aliexpress.com/_c3uz2Isv | Aliexpress |
| Ultrasonic sensor | Measures distance | 1 | 6 | https://a.aliexpress.com/_c35Zat1R | Aliexpress |
| TCRT5000 | Sensor | 1 | 7 | https://a.aliexpress.com/_c3RbgmiN | Aliexpress |
| Header pins | Soldering on pcb | 2 | 4 | https://a.aliexpress.com/_c4B0APx7 | Aliexpress |
| Mp1584 | Buck converter | 1 | 4.5 | https://a.aliexpress.com/_c4qnSguh | Aliexpress |
| Charging module | For charging battery | 1 | 2 | https://a.aliexpress.com/_c3Dtj3BL | Aliexpress |
| STM32 | Microcontroller | 1 | 6 | https://a.aliexpress.com/_c3GJD5FF | Aliexpress |
| Soldering Iron | For Soldering | 1 | 15 | https://epro.pk/product/soldering-iron-station-adjustable-temperature-esd-safe-kada-936-in-pakistan/ | Epro |
| Customs | - | - | 60 | - | AliExpress |
| Shipping | - | - | 20 | - | JLCPCB |
|  |  |  |  |  |  |
| Total | - | - | 200 | - | - |