// InputChannel.h

#ifndef _INPUTCHANNEL_h
#define _INPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class InputChannel
{
protected:
	uint8_t input_pin_ = 0;

public:
	virtual ~InputChannel() = default;
	InputChannel(uint8_t input_pin);

	virtual uint8_t read();
	virtual void setup();
};


#endif
