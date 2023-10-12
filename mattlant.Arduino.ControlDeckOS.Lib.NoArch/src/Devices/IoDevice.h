// IoDevice.h

// ReSharper disable CppClangTidyModernizeMacroToEnum
#ifndef _IODEVICE_h
#define _IODEVICE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define CHANNEL0_BITMASK 0b0000000000000001
#define CHANNEL1_BITMASK 0b0000000000000010
#define CHANNEL2_BITMASK 0b0000000000000100
#define CHANNEL3_BITMASK 0b0000000000001000
#define CHANNEL4_BITMASK 0b0000000000010000
#define CHANNEL5_BITMASK 0b0000000000100000
#define CHANNEL6_BITMASK 0b0000000001000000
#define CHANNEL7_BITMASK 0b0000000010000000

class IoDevice
{
protected:
	bool has_started_ = false;
	virtual void begin_();
	virtual void process_();

public:
	virtual ~IoDevice() = default;
	void begin();
	void process();
};


#endif
