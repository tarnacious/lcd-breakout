# 4 Digit LCD example 

Arduino Uno example.

## Requires

Everything should build with the following packages installed on a Debian 10
system.

    gcc-avr
    binutils-avr
    gdb-avr
    avr-libc
    avrdude
    make
    git

## Building

Install dependencies.

    make setup

Compile, link and prepare

    make

Flash 

    make flash


## Serial

Read from the Arduiono serial. (ctrl-a ctrl-\ to exit)

    screen /dev/ttyUSB0 115200
