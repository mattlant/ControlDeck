// analog_test.h

#ifndef _ANALOG_TEST_h
#define _ANALOG_TEST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Arduino.h>

namespace analog_test
{



	void setup();


	void loop();
}

#endif

