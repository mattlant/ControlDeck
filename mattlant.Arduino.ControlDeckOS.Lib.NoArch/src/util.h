// util.h

#ifndef _UTIL_h
#define _UTIL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

#define IO_DEBUG 0  // SET TO 0 OUT TO REMOVE TRACES
#define DBGPRINT 1    // SET TO 0 OUT TO REMOVE TRACES

#if DBGPRINT
#define DBG_BEGIN(...)		Serial.begin(__VA_ARGS__);
#define DBG_PRINT(...)		Serial.print(__VA_ARGS__)
#define DBG_WRITE(...)		Serial.write(__VA_ARGS__)
#define DBG_PRINTLN(...)	Serial.println(__VA_ARGS__)
#else
#define SER_BEGIN(...) 
#define SER_PRINT(...) 
#define SER_WRITE(...)
#define SER_PRINTLN(...) 
#endif

void func_decl();


#define USE_LOOP_COUNTER

#define LC_LOOPS_TO_AVG 5

#ifdef USE_LOOP_COUNTER

void lc_process();




#endif
