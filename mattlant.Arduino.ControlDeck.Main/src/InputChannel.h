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

public:
	virtual ~InputChannel();
	InputChannel();



	virtual int read_int();
	virtual uint8_t read_byte();
	virtual bool read_bit();
	virtual void setup();
};


#endif
