// 
// 
// 

#include "MuxInputDevice.h"

#include "../util.h"

MuxInputDevice::MuxInputDevice(InputDevice* signal_in_device, OutputDevice* select_out_device,
                                 byte select_bit_count, byte select_bit_pins[],
                                 byte signal_channel): InputDevice(),
                                                   select_bit_count_(select_bit_count),
                                                   signal_channel_(signal_channel),
                                                   select_channels_(select_bit_pins),
                                                   signal_input_device_(signal_in_device),
                                                   select_output_device_(select_out_device)
{
	channel_count_ = 2 ^ select_bit_count;
}


int MuxInputDevice::read(byte channel)
{
	//SET INPUT MODE
	return bitRead(cached_values, channel);
}

void MuxInputDevice::begin_()
{
	InputDevice::begin_();
	signal_input_device_->begin();
	select_output_device_->begin();

}

void MuxInputDevice::set_channel(int channel)
{
	for (int i = 0; i < select_bit_count_; i++)
	{
		select_output_device_->write(select_channels_[i], channel & (1 << i));
	}
}

void MuxInputDevice::process_()
{
	cached_values = read_digital_multi();
}

int MuxInputDevice::read_digital_multi()
{
	int value = 0;
	for(int in_channel = 0; in_channel < channel_count_; in_channel++)
	{
		set_channel(in_channel);
		delayMicroseconds(1);
		int channel_value = signal_input_device_->read(signal_channel_);
		bitWrite(value, in_channel, channel_value);
	}
	return value;
}
