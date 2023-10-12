// MainBoardInputChannel.h

#ifndef _MAINBOARDPINCHANNEL_h
#define _MAINBOARDPINCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "InputDevice.h"

class MainBoardInputDevice : public InputDevice
{

public:
	template <class ... Args>
	explicit MainBoardInputDevice(Args... args);

	void set_input_modes(byte channel, byte mode);

	int read(byte pin_id) override;
	void begin_() override;
	byte* input_modes_ = nullptr;
};

template<typename... Args>
MainBoardInputDevice::MainBoardInputDevice(Args... args): InputDevice(args...)
{
}

#endif
