// PFC8574InputChannel.h

#ifndef _PFC8574INPUTCHANNEL_h
#define _PFC8574INPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "InputChannel.h"
#include <PCF8574.h>

#include "DigitalInputChannel.h"

class PFC8574InputChannel : public DigitalInputChannel
{
public:
	//TODO: Inject the board itself so it can be reused and started across all inputs.
	PFC8574InputChannel(uint8_t pin, PCF8574* io_board);


public:
	int read() override;
	void setup() override;

protected:
	PCF8574* io_board_;
};

#endif
