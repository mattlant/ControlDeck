// 
// 
// 

#include "PFC8574InputChannel.h"

PFC8574InputChannel::PFC8574InputChannel(uint8_t pin, PCF8574* io_board): DigitalInputChannel(pin),
	io_board_(io_board)
{
}

int PFC8574InputChannel::read()
{
	return io_board_->digitalRead(pin_);
}

void PFC8574InputChannel::setup()
{
	io_board_->pinMode(pin_, INPUT);
	io_board_->begin();
}



