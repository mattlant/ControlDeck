// DigitalInputChannel.h

#ifndef _DIGITALINPUTCHANNEL_h
#define _DIGITALINPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "InputChannel.h"

class DigitalInputChannel: public InputChannel
{
public:
	explicit DigitalInputChannel(uint8_t pin);

protected:
	uint8_t pin_ = 0;

};

#endif

