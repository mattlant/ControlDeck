#include "OutputDevice.h"


void OutputDevice::ctor_init_helper_(int index)
{
	// No args passed to ctor
}


void OutputDevice::pulse(byte channel, int duration)
{
	if (channel_pulse_ == nullptr)
		channel_pulse_ = new PulseState[channel_count_];

	write(channel, HIGH);
	channel_pulse_[channel].end = millis() + duration;
}

void OutputDevice::write_digital_multi(int value)
{
	for (byte channel = 0; channel < channel_count_; channel++)
		write(channel_map_[channel], value & 1 << channel);
}

void OutputDevice::process_pulse_()
{
	for (byte i = 0; i < channel_count_; i++)
	{
		if (channel_pulse_[i].end != 0 && channel_pulse_[i].end < millis())
		{
			write(i, LOW);
			channel_pulse_[i].end = 0;
		}
	}
}

void OutputDevice::process_()
{
	IoDevice::process_();
	process_pulse_();
}

//OutputDevice* OutputDevice::use_output_line(byte line_id)
//{
//	return this;
//}
