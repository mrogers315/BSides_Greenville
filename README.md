Of course\! Here is a GitHub README that explains how to set up and load software to a CH32V003 microcontroller.

-----

# Getting Started with the CH32V003

This guide provides a straightforward method for setting up a development environment, compiling code, and flashing firmware to the **CH32V003**, an ultra-low-cost RISC-V microcontroller by WCH.

This setup uses the open-source `ch32v003fun` toolchain and a **WCH-LinkE** programmer.

-----

## Prerequisites

### Hardware

  * **CH32V003 Development Board**: Any board featuring the CH32V003 microcontroller.
  * **WCH-LinkE Programmer**: A debugger/programmer that supports SWDIO for WCH microcontrollers.
  * **USB Cable**: To connect the WCH-LinkE to your computer.

### Software

  * **Git**: For cloning the necessary repositories.
  * **RISC-V Toolchain**: A compiler for the RISC-V architecture.
  * **minichlink**: A tool for flashing firmware using the WCH-LinkE.

-----

## 1\. Software Setup

These steps will guide you through installing the necessary compiler and flashing tools.

### Install the RISC-V Toolchain

You can download a pre-built toolchain or build it from source. The easiest method is to download it.

1.  Go to the [xPack GNU RISC-V Embedded GCC releases page](https://github.com/xpack-dev-tools/riscv-none-embed-gcc-xpack/releases).
2.  Download the latest version appropriate for your operating system (Windows, macOS, or Linux).
3.  Extract the archive to a known location (e.g., `C:\toolchains\` on Windows or `/opt/toolchains/` on Linux/macOS).
4.  **Add the toolchain's `bin` directory to your system's PATH.** This allows you to run the compiler from any terminal.
      * **Windows:** Search for "Edit the system environment variables," click "Environment Variables," find "Path" in the "System variables" list, click "Edit," and add the full path to the `bin` folder (e.g., `C:\toolchains\xpack-riscv-none-embed-gcc-12.3.0-1\bin`).
      * **Linux/macOS:** Add the following line to your shell profile (e.g., `~/.bashrc`, `~/.zshrc`):
        ```bash
        export PATH="/opt/toolchains/xpack-riscv-none-embed-gcc-12.3.0-1/bin:$PATH"
        ```

### Install `minichlink`

This tool is used to flash the firmware onto the CH32V003.

1.  **Clone the repository:**

    ```bash
    git clone https://github.com/cnlohr/minichlink
    ```

2.  **Build the tool:**

      * **Linux/macOS:**
        ```bash
        cd minichlink
        make
        ```
      * **Windows:** Follow the build instructions in the `minichlink` repository, which typically involve using a tool like MSYS2 or Cygwin.

3.  **Install udev rules (Linux only):** This step is crucial for allowing `minichlink` to access the WCH-LinkE programmer without root privileges.

    ```bash
    cd minichlink
    sudo cp 99-wch-link.rules /etc/udev/rules.d/
    sudo udevadm control --reload-rules && sudo udevadm trigger
    ```

-----

## 2\. Project Setup & Build

Now you can get a sample project and compile it.

### Clone the `ch32v003fun` Example Project

The `ch32v003fun` project provides an excellent starting point with a pre-configured build system and examples.

```bash
git clone https://github.com/cnlohr/ch32v003fun
cd ch32v003fun/examples/blink
```

### Build the Code

Inside the `blink` example directory, run the `make` command. This will compile the C code and create a firmware file (`blink.hex`).

```bash
make
```

If the build is successful, you will see output from the compiler and a new `blink.hex` file will be present in the directory.

-----

## 3\. Flashing the Microcontroller

With the firmware built, you can now flash it to the chip.

### Connect the Hardware

1.  Connect the **WCH-LinkE** to your computer via USB.
2.  Connect the **WCH-LinkE** to the CH32V003 board. The connection requires at least three wires:
      * `SWDIO` -\> `SWDIO` (Pin `PC1` on the CH32V003)
      * `GND` -\> `GND`
      * `3.3V` -\> `3.3V`

### Flash the Firmware

Use the `minichlink` tool you built earlier to upload the `.hex` file. The tool should be located in the `minichlink` directory.

From the `ch32v003fun/examples/blink` directory, run the following command. You may need to adjust the path to the `minichlink` executable.

```bash
../../minichlink/minichlink -w blink.hex
```

If you want to flash and then immediately start a serial monitor to view output (if your code uses it), you can add the `-p` flag:

```bash
../../minichlink/minichlink -w blink.hex -p
```

You should see output confirming that the flash was successful. The LED on your CH32V003 board should now be blinking\! 🎉

-----

## Troubleshooting

  * **`make: riscv-none-embed-gcc: Command not found`**: This means the RISC-V toolchain is not in your system's PATH. Double-check your environment variable setup.
  * **`minichlink` permission errors (Linux)**: Ensure you have correctly installed the udev rules. You may need to unplug and replug the WCH-LinkE after setting them up.
  * **Flashing fails**: Check your wiring. Ensure `SWDIO`, `GND`, and `3.3V` are all connected correctly and securely between the WCH-LinkE and the CH32V003 board.
