// MainBoardInputChannel.h

#ifndef _MAINBOARDPINCHANNEL_h
#define _MAINBOARDPINCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "DigitalInputChannel.h"
#include "InputChannel.h"

class MainBoardInputChannel : public DigitalInputChannel
{

public:
	explicit MainBoardInputChannel(int input_ids[], int line_count);
	int read(int pin_id) override;
	void begin() override;
};

#endif
