// 
// 
// 

#include "InputChannel.h"

InputChannel::~InputChannel()
= default;


InputChannel::InputChannel()
= default;

int InputChannel::read_int()
{
	return 0;
}

uint8_t InputChannel::read_byte()
{
	return read_int();
}

bool InputChannel::read_bit()
{
	return read_int();
}


void InputChannel::setup()
{
}
