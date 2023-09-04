// MainBoardInputChannel.h

#ifndef _MAINBOARDPINCHANNEL_h
#define _MAINBOARDPINCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "InputChannel.h"

class MainBoardInputChannel : public InputChannel
{

public:
	explicit MainBoardInputChannel(uint8_t input_pin);
	uint8_t read() override;
	void setup() override;

};


#endif
