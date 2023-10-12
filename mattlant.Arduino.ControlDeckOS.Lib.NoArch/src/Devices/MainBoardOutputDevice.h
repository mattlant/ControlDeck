// MainBoardOutputChannel.h

#ifndef _MAINBOARDOUTPUTCHANNEL_h
#define _MAINBOARDOUTPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "OutputDevice.h"

class MainBoardOutputDevice : public OutputDevice
{
public:
	//MainBoardOutputDevice(byte output_pins[], byte output_pins_count);
	template <class ... Args>
	MainBoardOutputDevice(Args ... args);

	void begin_() override;

	void write(byte output_pin, int value) override;
};


template<typename... Args>
MainBoardOutputDevice::MainBoardOutputDevice(Args... args): OutputDevice(args...)
{
}

#endif
