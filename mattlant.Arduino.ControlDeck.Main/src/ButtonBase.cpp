// 
// 
// 

#include "ButtonBase.h"
#include "util.h"


ButtonBase::ButtonBase(uint8_t input_pin, int button_number): input_pin_(input_pin),
                                                              button_number_(button_number)
{
}

void ButtonBase::state_changed(uint8_t current_state)
{
}

void ButtonBase::setup()
{
	pinMode(input_pin_, INPUT);
}

void ButtonBase::process()
{
	const uint8_t current_state = !digitalRead(input_pin_);
	//SER_PRINTLN("BUTTON_PROC");
	if (last_input_state_ != current_state)
	{
		SER_PRINT("CHANGEDSTATE=");
		SER_PRINTLN(current_state == HIGH ? "ON" : "OFF");

		this->state_changed(current_state);
		last_input_state_ = current_state;
	}
}

void ButtonBase::set_joystick(Joystick_& joystick)
{
	joystick_ = &joystick;
}
