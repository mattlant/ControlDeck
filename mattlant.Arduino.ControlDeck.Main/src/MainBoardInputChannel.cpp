// 
// 
// 

#include "MainBoardInputChannel.h"

MainBoardInputChannel::MainBoardInputChannel(uint8_t input_pin): InputChannel(input_pin)
{
}

uint8_t MainBoardInputChannel::read()
{
	return digitalRead(input_pin_);
}

void MainBoardInputChannel::setup()
{
	pinMode(input_pin_, INPUT);
}



