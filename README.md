# bitTree

The bitTree is a versatile, strictly limited edition DIY gadget that combines the Christmas season with technology and creativity. With features such as individually controllable LEDs, melodies and programmability, it is ideal for hobbyists and technology enthusiasts - from beginners to experienced developers. Thanks to the USB-C connection and an Arduino-compatible microcontroller, there are virtually no limits to your projects.

## Hardware

### Pin Assignments

| Component         |               Direction | PORT - PIN | Arduino-PIN |                      Comment |
|:------------------|------------------------:|-----------:|------------:|-----------------------------:|
| ATmega328PB       |                       - |          - |           - | With Micronucleus bootloader |
| Led 1 (red)       |                    GPIO |        D-5 |           5 |      Low-Active (VCC driven) |
| Led 3 (red)       |                    GPIO |        C-4 |       18/A4 |      Low-Active (VCC driven) |
| Led 4 (red)       |                    GPIO |        C-3 |       17/A3 |      Low-Active (VCC driven) |
| Led 5 (red)       |                    GPIO |        C-2 |       16/A2 |     High-Active (MCU driven) |
| Led 6 (red)       |                    GPIO |        C-1 |       15/A1 |     High-Active (MCU driven) |
| Led 7 (red)       |                    GPIO |        C-0 |       14/A0 |     High-Active (MCU driven) |
| RGB LED 2 (blau)  |                    GPIO |        D-6 |           6 |     High-Active (MCU driven) |
| RGB LED 2 (red)   |                    GPIO |        B-1 |           9 |     High-Active (MCU driven) |
| RGB LED 2 (green) |                    GPIO |        B-2 |          10 |     High-Active (MCU driven) |
| Buzzer            |                    GPIO |        C-5 |       19/A5 |     High-Active (MCU driven) |
| Q-Touch           |                     PTC |        D-2 |           2 |                            - |
| USB D+            |                    GPIO |        B-3 |          11 |                            - |
| USB D-            |                    GPIO |        B-4 |          12 |                            - |
| Grove Adapter     | I²C/GPIO (only digital) |        E-0 |          23 |                            - |
| Grove Adapter     | I²C/GPIO (only digital) |        E-1 |          24 |                            - |
| SPI-Reset         |              Reset/GPIO |        C-6 |          22 |                            - |
| SPI-CIPO (MISO)   |                     SPI |        B-4 |          12 |                            - |
| SPI-COPI (MOSI)   |                     SPI |        B-3 |          11 |                            - |
| SPI-Clock         |                     SPI |        B-5 |          13 |                            - |

### Schematic and project files

The [schematic](./hardware/bitTree-Schematic.pdf) and the project files are located in the *hardware*-subdirectory. For additional information refer to the [Hardware README.md](./hardware/README.md).

## Updating the bitTree application

It is not yet possible to flash the application directly from the Arduino IDE. Therefore you have to install the tool [micronucleus commandline tool](https://github.com/micronucleus/micronucleus/tree/master/commandline) and use it as follows:

1. **Disconnect** the USB cable from the bitTree
2. Select the **Arduino Uno** as project board in the Arduino IDE
3. Export the project from the Arduino IDE: Menu “Sketch” -> “Export Compiled Binary”
4. Execute the following command in a console to **flash** the exported hex-file `micronucleus --run <path_to_repo>/bitTree/software/bitTree/build/arduino.avr.uno/bitTree.ino.hex`
5. **Connect** the USB cable to the bitTree (important: the above command must be started beforehand, as the tool is waiting for the bootloader)

What happens here in the background: As soon as the bitTree is supplied with power, the bootloader (micronucleus) starts. If there is no communication between the bitTree and the host (PC) within 2s, the flashed application starts, if a valid one is available.
The bootloader registers a USB device in the host, with which the “micronucleus commandline tool” communicates and can manipulate the flash in the bitTree.

## Build and install the bootloader

It is only required to build and update/install the bootloader, if you got a PCB directly from the assembly line. Refer to the [bootloader README](./software/bootloader/README.md) for some first instructions.

You also can use the hardware without the bootloader, but then you always have to program it with an external programmer. It is not possible to program the application through USB without the bootloader.

## Customize bitTree

The application code of the bitTree can be found in the source file [bitTree.ino](./software/bitTree/bitTree.ino) - this is where the states of the 6 red LEDs, the RGB star and the piezo buzzer are controlled.

### Implement new song

The song generated by the piezo buzzer can be changed by including a different, structurally identical header file instead of [jingle_bells.h](./software/bitTree/songs/jingle_bells.h).
This must contain a list `note song[]` of the consecutive notes and their note lengths.

### Adjusting the color of the star's RGB LED

The behavior of the RGB star is defined in thread 2.
The color of the RGB LED can be adjusted by changing the red, green and blue values in `enable_rgb_led()`.

### Change the flashing pattern of the red LEDs

The “random” flashing of the red LEDs is defined in thread 3.
Individual LEDs can be activated/deactivated by `enable_led()`.

### Use the Grove ecosystem

Thanks to the integrated Grove connection, the bitTree can be expanded with Grove modules such as sensors or network modules. Further information and examples can be found [here](https://wiki.seeedstudio.com/Grove_System/).
