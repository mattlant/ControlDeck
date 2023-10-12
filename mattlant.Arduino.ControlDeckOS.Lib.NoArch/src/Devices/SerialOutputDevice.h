// SerialOutputDevice.h

#ifndef _SERIALOUTPUTDEVICE_h
#define _SERIALOUTPUTDEVICE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "OutputDevice.h"

class SerialOutputDevice : public OutputDevice
{
public:
	void write(byte channel, int value) override;

	SerialOutputDevice(byte channel_count);
};

#endif

