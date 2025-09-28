---

# Getting Started with CH32V003 and MounRiver Studio



This guide provides a step-by-step tutorial for setting up a development environment, creating a project, and flashing firmware to the **CH32V003** microcontroller using **MounRiver Studio**.

MounRiver Studio is an all-in-one IDE that simplifies the development process, making it great for beginners.

***

## Prerequisites

### Hardware
* **CH32V003 Development Board**: Any board featuring the CH32V003 chip.
* **WCH-LinkE Programmer**: The official debugger/programmer for WCH microcontrollers.
* **USB Cable**: To connect the WCH-LinkE to your computer.

### Software
* **MounRiver Studio**: The integrated development environment (IDE).

***

## 1. Install MounRiver Studio

First, you need to download and install the IDE.

1.  Navigate to the [WCH MounRiver download page](http://www.mounriver.com/download).
2.  Download the latest version for your operating system (Windows is primarily supported).
3.  Run the installer and follow the on-screen instructions. The setup will automatically install the necessary toolchain and drivers for the WCH-LinkE.

***

## 2. Create a New Project

Let's create a simple "Blink" project from a template.

1.  Open MounRiver Studio.
2.  Go to **File** -> **New** -> **MounRiver Project**.
3.  In the "Target Chip" selection window, choose **CH32V003F4P6**. Click **Next**.
    
4.  Give your project a name (e.g., `CH32V003_Blink`).
5.  Select a project template. For a simple start, expand **GPIO** and choose **GPIO_Toggle**. This provides a pre-written code example to blink an LED.
6.  Click **Finish**.

The IDE will generate a project with all the necessary files, including the main C file (`Main.c`) with the blinking logic.

***

## 3. Build the Project

Compiling your code converts it into a machine-readable format that the microcontroller can execute.

1.  In MounRiver Studio, click the **Build** icon (the hammer 🔨) in the toolbar.
2.  Alternatively, go to **Project** -> **Build Project**.
3.  Wait for the process to complete. You can monitor the progress in the **Console** window at the bottom. A "Build Finished" message indicates success.

***

## 4. Connect the Hardware

Now, connect your programmer to the microcontroller board.

1.  Connect the **WCH-LinkE** to your computer via USB.
2.  Connect the WCH-LinkE to the CH32V003 board using the following pins:
    * `SWDIO` -> `SWDIO` (Pin `PC1` on the CH32V003)
    * `GND` -> `GND`
    * `3.3V` -> `3.3V`



**Important**: Ensure the connections are secure. A poor connection is the most common cause of flashing failures.

***

## 5. Flash the Microcontroller

Flashing (or "downloading") uploads your compiled code to the chip's memory.

1.  In MounRiver Studio, click the **Download** icon (the green arrow pointing down ⬇️) in the toolbar.
2.  The IDE will automatically detect the WCH-LinkE and the target chip.
3.  The console will display the flashing progress. A message like "Download success" or "Verify success" means the code has been successfully uploaded.

Your CH32V003 board's LED should now be blinking! 🎉

***

## Troubleshooting

* **WCH-LinkE Not Found**:
    * Ensure the WCH-LinkE is securely plugged into your computer's USB port.
    * Try reinstalling MounRiver Studio to make sure the drivers were installed correctly.
    * Check your system's device manager to see if the WCH-LinkE is recognized.

* **Download Failed**:
    * Double-check your wiring between the WCH-LinkE and the CH32V003. `SWDIO`, `GND`, and `3.3V` must all be correctly connected.
    * Ensure the CH32V003 board is receiving power.
    * Close and reopen MounRiver Studio and try again.
 
***
## Badge Details
<img width="668" height="680" alt="image" src="https://github.com/user-attachments/assets/8dfd9593-d4c0-4bfd-95ef-81f412da48ed" />

* **Pinout**:
  * Pin 1 - Marked with the Dot - SWIO
  * pin 2 - VCC (3.3V)
  * Pin 3 Ground

* **GPIO**:
  * 0 - PA2/A0
  * 1 - PA1/A1
  * 2 - PC4/A2
  * 3 - PD2/A3
  * 4 - PD3/A4
  * 5 - PD5/A5
  * 6 - PD6/A6
  * 7 - PD4/A7

