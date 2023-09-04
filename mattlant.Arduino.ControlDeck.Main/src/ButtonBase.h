// ButtonBase.h

#ifndef _JOYSTICKBUTTONBASE_h
#define _JOYSTICKBUTTONBASE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Joystick.h>

#include "InputChannel.h"
#include "OutputChannel.h"

class ButtonBase
{
public:
	ButtonBase(InputChannel* channel, int input_id, OutputChannel* output_channel, int output_id);
	virtual void setup();
	virtual void process();

protected:
	InputChannel* input_channel_;
	int input_id_;
	OutputChannel* output_channel_;
	int output_id_;

	uint8_t last_input_state_ = 0;

	uint8_t monitor_led = 8;
	virtual void state_changed(uint8_t current_state);
};


#endif
