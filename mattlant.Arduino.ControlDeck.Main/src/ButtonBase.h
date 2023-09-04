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

class ButtonBase
{
public:
	ButtonBase(InputChannel* channel, int button_number);
	virtual void setup();
	virtual void process();
	void set_joystick(Joystick_& joystick);

protected:
	Joystick_* joystick_;
	uint8_t button_number_;
	uint8_t last_input_state_ = 0;

	uint8_t monitor_led = 8;
	InputChannel* channel_;
	virtual void state_changed(uint8_t current_state);

};


#endif
