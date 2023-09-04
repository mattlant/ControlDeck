// InputChannel.h

#ifndef INPUTCHANNEL_h
#define INPUTCHANNEL_h

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
	virtual ~InputChannel();

	explicit InputChannel(int input_ids[], int input_count);


	virtual int read(int input_id);

	//Do any channel setup/start in derived begin method, such as setting pin directions
	virtual void begin();
};


#endif
