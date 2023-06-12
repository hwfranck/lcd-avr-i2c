# lcd-avr-i2c
This is the accompanying source code for [this article](https://hwfranck.com/posts/lcd-avr-i2c) on my blog.

A few lines of code are used to display the content shown on the picture below.

## Demo
![16x2 LCD displaying text and battery graphics](demo.jpg "The final result")

## Build instructions

Edit the [makefile](src/makefile) according to your board. Start by setting the `AVRDUDE_PORT` variable to the correct value.

### Ubuntu
---
install the dependencies :

    sudo apt update
    sudo apt install make gcc-avr avr-libc avrdude

Find your serial device :
- Disconnect the board from the computer
- Run `dmesg` in follow-mode : `sudo dmesg -Tw`
- Connect the board
- New entries should appear in the Terminal and contain the correct `ttyXXXn` value.
> [Current date and time] cdc_acm 1-1.1:1.0: ttyACM0: USB ACM device
- terminate `dmesg` using `Ctrl+C`
- Do not overwrite `/dev/`, only replace `ttyACM0` in the makefile

compile and flash the board :

    make
    make flash


### Windows
---
  * Download [AVR 8-Bit Toolchain (Windows)](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio/gcc-compilers)
  * Download [avrdude](https://github.com/avrdudes/avrdude/releases)
  * Obtain `make.exe` by extracting it from [winavr](https://sourceforge.net/projects/winavr/files/WinAVR/20100110/). After opening the installer as an archive, it's located under `utils/bin/`

Edit the `PATH` environment variable to access the utilities used here from anywhere or always use the full path.

Find the correct port :
- Open the Start Menu
- Type `device manager`
- Look under `Ports (COM & LPT)`
- Example : `USB Serial Device (COM3)`

compile and flash the board (from the command prompt) :

    make
    make flash
