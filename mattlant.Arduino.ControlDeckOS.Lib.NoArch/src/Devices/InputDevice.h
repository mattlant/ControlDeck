// InputDevice.h

#ifndef INPUTCHANNEL_h
#define INPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "IoDevice.h"


class InputDevice : public IoDevice
{
	template <class T, class... Rest>
	void ctor_init_helper_(int index, T first, Rest... rest);
	void ctor_init_helper_(int index);

protected:
	byte* channel_map_;
	byte channel_count_;

	bool is_analog_ = false;

public:
	template <class... Args>
	InputDevice(Args... args);


	virtual int read(byte channel) = 0;
	virtual int read_digital_multi();

	void set_to_analog();
	void set_to_digital();


	//virtual InputDevice* use_input_line(byte line_id);
};


template <typename T, typename... Rest>
void InputDevice::ctor_init_helper_(int index, T first, Rest... rest)
{
	channel_map_[index] = first;
	ctor_init_helper_(index + 1, rest...);
}

template <typename... Args>
InputDevice::InputDevice(Args... args) : channel_count_(sizeof...(args))
{
	channel_map_ = new byte[channel_count_];
	ctor_init_helper_(0, args...);
}


#endif
