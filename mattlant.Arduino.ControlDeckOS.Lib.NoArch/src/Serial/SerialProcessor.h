// SerialProcessor.h

#ifndef _SERIALPROCESSOR_h
#define _SERIALPROCESSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SerialProcessor
{
 protected:


 public:
	void begin();
	void process();
};

#endif

