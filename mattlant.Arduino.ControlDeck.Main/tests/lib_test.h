// LibraryTesting.h

#ifndef _LIBRARYTESTING_h
#define _LIBRARYTESTING_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif



namespace lib_test
{

	void setup();


	void loop();
}
#endif
