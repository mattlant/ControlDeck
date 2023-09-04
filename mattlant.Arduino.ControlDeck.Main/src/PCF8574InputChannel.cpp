// 
// 
// 

#include "PCF8574InputChannel.h"

PCF8574InputChannel::PCF8574InputChannel(uint8_t pin, PCF8574* io_board): DigitalInputChannel(pin),
                                                                          io_board_(io_board)
{
}

int PCF8574InputChannel::read_int()
{
	return io_board_->digitalRead(pin_);
}

void PCF8574InputChannel::setup()
{
	io_board_->pinMode(pin_, INPUT);
}



