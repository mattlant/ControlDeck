// 
// 
// 

#include "MainBoardInputChannel.h"

MainBoardInputChannel::MainBoardInputChannel(uint8_t pin): DigitalInputChannel(pin)
{
}

int MainBoardInputChannel::read()
{
	return digitalRead(pin_);
}

void MainBoardInputChannel::setup()
{
	pinMode(pin_, INPUT);
}



