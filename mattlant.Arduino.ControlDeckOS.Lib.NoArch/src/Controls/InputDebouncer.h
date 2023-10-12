// InputDebouncer.h

#ifndef INPUTDEBOUNCER_h
#define INPUTDEBOUNCER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class InputDebouncer
{
private:
	byte _keepValue;
	byte _bounce;

public:
	InputDebouncer(): _keepValue(0x0), _bounce(0x0)
	{
	}

	bool isDebounced(byte value, byte debounceCount);
};

#endif

