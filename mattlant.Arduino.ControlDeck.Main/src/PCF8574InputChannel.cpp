// 
// 
// 

#include <PCF8574.h>

#include "PCF8574InputChannel.h"


PCF8574InputChannel::PCF8574InputChannel(uint8_t io_address, int input_ids[], int input_count): InputChannel(input_ids, input_count)
                                                                        
{
	io_board_ = new PCF8574(io_address);
}

int PCF8574InputChannel::read(int pin_id)
{
	return io_board_->digitalRead(pin_id, true);
}

void PCF8574InputChannel::begin()
{
	//for (int i = 0; i < input_count_; i++)
	//	io_board_->pinMode(input_ids_[i], INPUT_PULLUP);
	//io_board_->begin();
	for (int i = 0; i < 8; i++)
		io_board_->pinMode(0, INPUT_PULLUP);
	io_board_->begin();
}



