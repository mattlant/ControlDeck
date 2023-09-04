// DigitalInputChannel.h

#ifndef _DIGITALINPUTCHANNEL_h
#define _DIGITALINPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "InputChannel.h"

//TODO: REMOVE THIS CLASS - HAS NO MORE USE
class DigitalInputChannel: public InputChannel
{
public:
	explicit DigitalInputChannel(int line_ids[], int line_count);


};

#endif

