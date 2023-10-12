// NullOutputChannel.h

#ifndef _NULLOUTPUTCHANNEL_h
#define _NULLOUTPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "OutputDevice.h"

class NullOutputDevice : public OutputDevice
{
public:
	NullOutputDevice();
};
#endif

