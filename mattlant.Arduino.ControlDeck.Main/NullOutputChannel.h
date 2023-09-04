// NullOutputChannel.h

#ifndef _NULLOUTPUTCHANNEL_h
#define _NULLOUTPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "src/OutputChannel.h"

class NullOutputChannel : public OutputChannel
{
public:
	NullOutputChannel()
		: OutputChannel(nullptr, 0)
	{
	}
};


#endif

