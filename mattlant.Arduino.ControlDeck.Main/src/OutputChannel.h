// OutputChannel.h

#ifndef _OUTPUTCHANNEL_h
#define _OUTPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class OutputChannel
{
protected:
	int* output_ids_; //int array
	int output_count_;

public:
	explicit OutputChannel(int output_ids[], int output_count): output_ids_(output_ids), output_count_(output_count)
	{
	}

	~OutputChannel() = default;

	virtual void setup()
	{
	}

	virtual void write(int output_id, int value)
	{
	}
};


#endif
