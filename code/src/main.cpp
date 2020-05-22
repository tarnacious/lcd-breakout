#include <avr/io.h>
#include <util/delay.h>
#include <Arduino.h>
#include <HardwareSerial.h>
#include <SevenSegment.h>
#include <stdio.h>

#define CLOCK 3 // Arudino digital 44 -> AY0438 clock
#define DATA 4	 // Arudino digital 46 -> AY0438 data
#define LOAD 5  // Arudino digital 45 -> AY0438 load

SevenSegment screen(CLOCK, DATA, LOAD);

void print_millis(unsigned long milli)
{
  //3600000 milliseconds in an hour
  unsigned long hr = milli / 3600000;
  milli = milli - 3600000 * hr;
  //60000 milliseconds in a minute
  unsigned long min = milli / 60000;
  milli = milli - 60000 * min;
  //1000 milliseconds in a second
  unsigned long sec = milli / 1000;

  char result[6];
  sprintf(result, "%02d:%02d", int(min), int(sec));
  screen.print(result);
}

void run_lcd(void)
{
  unsigned long duration = 5000; //1800000;

  Serial.print("Setup\n");
	screen.begin("AY0438","8.8|8.8");
	char message[] = "yayy";
  screen.print(message);
  delay(1000);
  screen.clear();
  delay(1000);

  print_millis(duration);
  delay(1000);
  unsigned long start_millis = millis();

	for (;;) {
    unsigned long current_millis = millis();
    unsigned long elapsed_millis = current_millis - start_millis;
    if (elapsed_millis > duration) {
      for(int i = 0; i < 8; i++) {
        print_millis((unsigned long)0);
        delay(400);
        screen.clear();
        delay(400);
      }
      delay(2000);
      print_millis(duration);
      delay(1000);
      start_millis = millis();
    } else {
      print_millis(duration - elapsed_millis);
    }
    delay(1);
  }
	screen.clear();
}


int main(void)
{
	init();
	Serial.begin(115200);
  run_lcd();
	return 0;
}
