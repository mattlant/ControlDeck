// AnalogJoystickControl.h

#ifndef _ANALOGJOYSTICKCONTROL_h
#define _ANALOGJOYSTICKCONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Control.h"

#define AXIS_SENSITIVITY 5

class AnalogJoystickControl : public Control
{
public:
	AnalogJoystickControl(InputDevice* const input_device, OutputDevice* const output_device,
		const byte x_input_channel, const byte y_input_channel, byte x_output_channel, byte y_output_channel, int sampling_interval = 10)
		: Control(input_device, output_device, sampling_interval),
		  x_input_channel_(x_input_channel),
		  y_input_channel_(y_input_channel), x_output_channel_(x_output_channel), y_output_channel_(y_output_channel)
	{
	}

	void setup_impl() override;

	void process() override;

protected:
	int x_value_;
	int y_value_;
	byte x_input_channel_;
	byte y_input_channel_;
	byte x_output_channel_;
	byte y_output_channel_;

public:

};


#endif
