// InputChannelFactory.h

#ifndef _INPUTCHANNELFACTORY_h
#define _INPUTCHANNELFACTORY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class InputChannelFactoryClass
{
 protected:


 public:
	enum channel_type
	{
		DigitalMainBoard,
		PFC8574
	};

	void create(channel_type type);

};

extern InputChannelFactoryClass InputChannelFactory;

#endif

