// 
// 
// 

#include "PCF8574InputChannel.h"

PCF8574InputChannel::PCF8574InputChannel(uint8_t io_address, int input_ids[], int input_count): DigitalInputChannel(input_ids, input_count)
                                                                        
{
	io_board_ = new PCF8574(io_address);
}

int PCF8574InputChannel::read(int pin_id)
{
	return io_board_->digitalRead(pin_id);
}

void PCF8574InputChannel::setup()
{
	for (int i = 0; i < input_count_; i++)
		io_board_->pinMode(input_ids_[i], INPUT);
	io_board_->begin();
}



