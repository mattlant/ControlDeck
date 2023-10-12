// MuxInputChannel.h

#ifndef MUXINPUTCHANNEL_h
#define MUXINPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "InputDevice.h"
#include "OutputDevice.h"

class MuxInputDevice : public InputDevice
{
public:
	MuxInputDevice(InputDevice* signal_in_device, OutputDevice* select_out_device, 
		byte select_bit_count, byte select_bit_pins[], byte signal_channel);
	template <class ... Args>
	MuxInputDevice(InputDevice* signal_in_device, byte signal_channel, OutputDevice* select_out_device, Args ... select_channels);

	int read(byte channel) override;
	void begin_() override;

protected:
	void set_channel(int channel);
	void process_() override;

public:
	int read_digital_multi() override;

protected:
	byte select_bit_count_;
	byte signal_channel_;
	byte* select_channels_;
	int cached_values = 0;

	InputDevice* signal_input_device_;
	OutputDevice* select_output_device_;
};

template<typename... Args>
MuxInputDevice::MuxInputDevice(InputDevice* signal_in_device, byte signal_channel, OutputDevice* select_out_device, Args... select_channels): InputDevice(),
                                                   select_bit_count_(sizeof...(select_channels)),
                                                   
                                                   signal_channel_(signal_channel),
                                                   signal_input_device_(signal_in_device),
                                                   select_output_device_(select_out_device)
{
	select_channels_ = new byte[sizeof...(select_channels)];
    int index = 0;
    ((select_channels_[index++] = select_channels), ...);
	channel_count_ = 2 ^ select_bit_count_;
}


#endif
