// analog_test.h

#ifndef OLED_TEST_h
#define OLED_TEST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Arduino.h>

namespace oled_test
{

	byte x_pin = A0;
byte y_pin = A1;

byte x_led_pin = 7;
byte y_led_pin = 9;

int x_val;
int y_val;


	void setup();


	void loop();
}

#endif

