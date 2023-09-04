// 
// 
// 

#include "InputChannel.h"

InputChannel::InputChannel(uint8_t input_pin): input_pin_(input_pin)
{
}

uint8_t InputChannel::read()
{
	return LOW;
}

void InputChannel::setup()
{
}



