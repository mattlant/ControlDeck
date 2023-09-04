// InputChannel.h

#ifndef _INPUTCHANNEL_h
#define _INPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class InputChannel
{
protected:
	int* input_ids_;
	int input_count_;

public:
	virtual ~InputChannel();
	explicit InputChannel(int input_ids[], int input_count);



	virtual int read_int(int input_id);
	virtual uint8_t read_byte(int input_id);
	virtual bool read_bit(int input_id);
	virtual void setup();
};


#endif
