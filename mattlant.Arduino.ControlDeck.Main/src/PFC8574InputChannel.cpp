// 
// 
// 

#include "PFC8574InputChannel.h"

PFC8574InputChannel::PFC8574InputChannel(uint8_t input_pin, PCF8574* io_board): InputChannel(input_pin),
	io_board_(io_board)
{
}

uint8_t PFC8574InputChannel::read()
{
	return io_board_->digitalRead(input_pin_);
}

void PFC8574InputChannel::setup()
{
	io_board_->pinMode(input_pin_, INPUT);
	io_board_->begin();
}



