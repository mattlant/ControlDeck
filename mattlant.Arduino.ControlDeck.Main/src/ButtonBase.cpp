// 
// 
// 

#include "ButtonBase.h"
#include "util.h"



void ButtonBase::state_changed(uint8_t current_state)
{
}

ButtonBase::ButtonBase(InputChannel* channel, int button_number): channel_(channel), button_number_(button_number)
{
}

void ButtonBase::setup()
{
	channel_->setup();
}

void ButtonBase::process()
{
	const uint8_t current_state = channel_->read_byte();
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
