ARDUINO_SRC = ./ArduinoCore-avr/cores/arduino/
ARDUINO_VARIANTS_PATH =./ArduinoCore-avr/variants/standard/
SEVEN_SEGMENT = ./arduino-seven-segment

OBJFILES = $(shell find $(ARDUINO_SRC) -maxdepth 1 -name '*.[c|S]' -printf '%f\n' | sed -e 's/\.[c|S]/\.o/g' | uniq | xargs echo)
OBJFILES += $(shell find $(ARDUINO_SRC) -maxdepth 1 -name '*.cpp' -not -name 'main.cpp' -printf '%f ' | sed -e 's/\.cpp/\.o/g')
OBJFILES += $(shell find src/ -maxdepth 1 -name '*.cpp' -printf '%f ' | sed -e 's/\.cpp/\.o/g')
OBJFILES += SevenSegment.o
CPPFILES += $(shell find $(ARDUINO_SRC) -maxdepth 1 -name '*.cpp' -not -name 'main.cpp' -printf '%f ')

MCU = atmega328p
CC = avr-gcc
CLOCK = 16000000
LIB = -I$(ARDUINO_SRC) -I$(ARDUINO_VARIANTS_PATH) -I$(SEVEN_SEGMENT)
CFLAGS = -std=c99 -mmcu=$(MCU) -Wall -ffunction-sections -fdata-sections -Os $(LIB) -DF_CPU=$(CLOCK)
CPPFLAGS = -std=c++11 -Os -mmcu=$(MCU) -Wall -DF_CPU=$(CLOCK) $(LIB) -DARDUINO=100
AFLAGS = -mmcu=$(MCU) $(LIB) -DF_CPU=$(CLOCK)

all: main.hex

wiring_pulse.o: $(ARDUINO_SRC)wiring_pulse.c $(ARDUINO_SRC)wiring_pulse.S
	$(CC) -c $(CPPFLAGS) $(ARDUINO_SRC)wiring_pulse.c $(ARDUINO_SRC)wiring_pulse.S

%.o: src/%.cpp 
	$(CC) -c $(CPPFLAGS) $< -o $@

%.o: $(SEVEN_SEGMENT)/%.cpp 
	$(CC) -c $(CPPFLAGS) $< -o $@

%.o: $(ARDUINO_SRC)%.c
	$(CC) -c $(CFLAGS) $< -o $@

%.o: $(ARDUINO_SRC)%.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

%.o: $(ARDUINO_SRC)%.S
	$(CC) -c $(CFLAGS) $< -o $@

main.elf: $(OBJFILES)
	$(CC) $(AFLAGS) $(OBJFILES) -o $@

main.hex: main.elf
	avr-objcopy -O ihex main.elf main.hex

flash: main.hex
	avrdude -v -p atmega328p -c arduino -P /dev/ttyUSB0 -b 57600 -D -U flash:w:main.hex:i

clean:
	rm -rf *.o
	rm -rf *.hex
	rm -rf *.elf

setup: 
	git clone https://github.com/supercrab/arduino-seven-segment.git
	git clone https://github.com/arduino/ArduinoCore-avr.git
