// util.h

#ifndef _UTIL_h
#define _UTIL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

#define SERPRINT 1    // SET TO 0 OUT TO REMOVE TRACES

#if SERPRINT
#define SER_BEGIN(...)		Serial.begin(__VA_ARGS__);
#define SER_PRINT(...)		Serial.print(__VA_ARGS__)
#define SER_WRITE(...)		Serial.write(__VA_ARGS__)
#define SER_PRINTLN(...)	Serial.println(__VA_ARGS__)
#else
#define SER_BEGIN(...) 
#define SER_PRINT(...) 
#define SER_WRITE(...)
#define SER_PRINTLN(...) 
#endif
