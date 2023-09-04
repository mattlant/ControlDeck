// 
// 
// 

#include "MainBoardInputChannel.h"

MainBoardInputChannel::MainBoardInputChannel(uint8_t pin): DigitalInputChannel(pin)
{
}

int MainBoardInputChannel::read_int()
{
	return digitalRead(pin_);
}

void MainBoardInputChannel::setup()
{
	pinMode(pin_, INPUT);
}



