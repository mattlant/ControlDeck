// KeyboardOutputChannel.h

#ifndef _KEYBOARDOUTPUTCHANNEL_h
#define _KEYBOARDOUTPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "OutputChannel.h"

class KeyboardOutputChannel : public OutputChannel
{
 protected:


 public:
	KeyboardOutputChannel(int output_ids[], int output_count)
		: OutputChannel(output_ids, output_count)
	{
	}

	void begin() override;
	void write(int output_id, int value) override;
};

#endif

