// KeyboardOutputChannel.h

#ifndef _KEYBOARDOUTPUTCHANNEL_h
#define _KEYBOARDOUTPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Keyboard.h>
#include "OutputDevice.h"

class KeyboardOutputDevice : public OutputDevice
{
protected:


public:
	KeyboardOutputDevice();

	void begin_() override;

	void write(byte output_id, int value) override;
};

#endif
