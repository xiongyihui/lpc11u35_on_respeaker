LPC11U35 on Respeaker
=====================

The LPC11U35 microcontroller on Respeaker provide a USB to UART bridge, a colorful LEDs driver and touch buttons.
The repository contains source code running on LPC11U35 microcontroller. It is based on mbed SDK.


### Requirements
+ [gcc arm embedded toolchain](https://launchpad.net/gcc-arm-embedded)
+ make
+ python (optional, for tools/flash.py running on windows)
+ lpcrc on linux/mac - `cd tools/lpcrc && make`

### Get started
1. press & hold the '-' button, and then power on the Respeaker, the Respeker will run into bootloader
2. on windows, run `make flash`; on linux/mac, `make && dd if=lpc11u35.bin of=/path/to/firmware.bin` (replace `/path/to` with the right path)




