// 
// 
// 

#include "InputChannel.h"

InputChannel::~InputChannel()
= default;

InputChannel::InputChannel(int input_ids[], int input_count): input_ids_(input_ids), input_count_(input_count)
{
	
}


int InputChannel::read_int(int input_id)
{
	return 0;
}

uint8_t InputChannel::read_byte(int input_id)
{
	return read_int(input_id);
}

bool InputChannel::read_bit(int input_id)
{
	return read_int(input_id);
}


void InputChannel::setup()
{
	//Do any channel in derived setup, such as setting pin directions
}
