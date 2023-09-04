// KeyboardOutputChannel.h

#ifndef _KEYBOARDOUTPUTCHANNEL_h
#define _KEYBOARDOUTPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Keyboard.h>
#include "OutputChannel.h"

class KeyboardOutputChannel : public OutputChannel
{
protected:


public:
	KeyboardOutputChannel()
		: OutputChannel(nullptr, 0)
	{
	}

	void begin() override
	{
		Keyboard.begin();
	}

	void write(int output_id, int value) override
	{
		if (value == 0)
			return;
		Keyboard.write(output_id);
	}
};

#endif
