// OutputChannel.h

#ifndef OUTPUTCHANNEL_h
#define OUTPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IoDevice.h"

struct PulseState
{
	unsigned long end;
};


class OutputDevice : public IoDevice
{
	template <class T, class ... Rest>
	void ctor_init_helper_(int index, T first, Rest ... rest);
	void ctor_init_helper_(int index);


protected:
	byte* channel_map_; 
	PulseState* channel_pulse_; 
	byte channel_count_;

public:
	template <class... Args>
	OutputDevice(Args... args);

	virtual void write(byte channel, int value) = 0;
	virtual void pulse(byte channel, int duration);

	//Non optimal write, utilizing multiple calls to this->write()
	virtual void write_digital_multi(int value);
	void process_pulse_();

protected:
	void process_() override;
	//virtual OutputDevice* use_output_line(byte line_id);
};


template<typename T, typename... Rest>
void OutputDevice::ctor_init_helper_(int index, T first, Rest... rest) {
    channel_map_[index] = first;
    ctor_init_helper_(index + 1, rest...);
}

template<typename... Args>
OutputDevice::OutputDevice(Args... args) : channel_count_(sizeof...(args)) {
    channel_map_ = new byte[channel_count_];
    ctor_init_helper_(0, args...);
}


#endif
