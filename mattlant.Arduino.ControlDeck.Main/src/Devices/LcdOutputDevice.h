// LcdOutputDevice.h

#ifndef _LCDOUTPUTDEVICE_h
#define _LCDOUTPUTDEVICE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <LiquidCrystal.h>

#include "../Devices/OutputDevice.h"

class LcdOutputDevice : public OutputDevice
{
public:
	LcdOutputDevice(int rs, int en, int d4, int d5, int d6, int d7, int channel_count);
	void begin_() override;

private:
	LiquidCrystal lcd_;
	int num_positions_;
	int last_values_[32];
	void map_to_lcd(int position, int value);
	void initialize_lcd();

public:
	void write(byte channel, int value) override;
};

#endif 


