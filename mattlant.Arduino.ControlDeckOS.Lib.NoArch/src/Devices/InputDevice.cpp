#include "InputDevice.h"


int InputDevice::read_digital_multi()
{
	int result = 0;
	for(int channel = 0; channel < channel_count_; channel++)
		if(read(channel_map_[channel]))
			bitSet(result, channel);

	return result;
}

void InputDevice::set_to_analog()
{
	is_analog_ = true;
}

void InputDevice::set_to_digital()
{
	is_analog_ = false;
}

void InputDevice::ctor_init_helper_(int index)
{
	// No args passed to ctor
}

