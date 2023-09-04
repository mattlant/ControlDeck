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
	int* input_ids_; //int array
	int input_count_;

public:
	virtual ~InputChannel()
	= default;

	explicit InputChannel(int input_ids[], int input_count): input_ids_(input_ids), input_count_(input_count)
	{
	}


	virtual int read(int input_id)
	{
		return 0;
	}

	//Do any channel setup/start in derived begin method, such as setting pin directions
	virtual void begin()
	{
	}
};


#endif
