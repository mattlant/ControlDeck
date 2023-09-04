// MainBoardOutputChannel.h

#ifndef _MAINBOARDOUTPUTCHANNEL_h
#define _MAINBOARDOUTPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "OutputChannel.h"

class MainBoardOutputChannel : public OutputChannel
{
public:
	MainBoardOutputChannel(int output_pins[], int output_pins_count);

	void begin() override;

	void write(int output_pin, int value) override;
};


#endif
