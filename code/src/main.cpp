#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <HardwareSerial.h>
#include <SevenSegment.h>

#define CLOCK 3 // Arudino digital 44 -> AY0438 clock
#define DATA 4	 // Arudino digital 46 -> AY0438 data
#define LOAD 5  // Arudino digital 45 -> AY0438 load

SevenSegment screen(CLOCK, DATA, LOAD);

int period = 1000;
unsigned long time_now = 0;

int led = 13;

void run_lcd(void)
{
  Serial.print("Setup\n");
	screen.begin("AY0438","8");

	// Turn on all segments and turn off 5 times
	for (int i=0; i<5; i ++){
    Serial.print("Turn all segments on\n");
		// Turn all known segments on
		screen.on();
		delay(500);

		// Turn all known segments off
    Serial.print("Turn all segments off\n");
		screen.clear();
		delay(500);
	}

  Serial.print("Count to 9");
	// Count to 9
	for (int i = 0; i < 10; i++){
		screen.printNumber(i);
		delay(200);
	}

	// Display all characters one by one
  Serial.print("all characters");
	screen.setAlignment(LEFT);
	char c[2];
	for (int i = 32; i<= 127; i++){
		c[0] = i;
		c[1] = 0;
		screen.print(c);
		delay(200);
	}
}

void flash_led(void)
{
	pinMode(led, OUTPUT);
	while(true){
		Serial.print("flash\n");
		digitalWrite(led, LOW);
		delay(500);
		digitalWrite(led, HIGH);
		delay(500);
	}
}

int main(void)
{
	init();
	Serial.begin(115200);
  run_lcd();
	return 0;
}
