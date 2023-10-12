// analog_test.h

#ifndef _LCD_TEST_h
#define _LCD_TEST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Arduino.h>
#include <LiquidCrystal.h>

namespace lcd_test
{

	void setup();


	void loop();
}

#endif

