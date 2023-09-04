// OutputChannel.h

#ifndef OUTPUTCHANNEL_h
#define OUTPUTCHANNEL_h

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
	explicit OutputChannel(int output_ids[], int output_count);

	~OutputChannel();

	virtual void begin();

	virtual void write(int output_id, int value);
};


#endif
