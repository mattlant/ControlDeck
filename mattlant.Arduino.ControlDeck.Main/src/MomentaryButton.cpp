// 
// 
// 

#include "util.h"
#include "MomentaryButton.h"
#include "ButtonBase.h"


MomentaryButton::MomentaryButton(InputChannel* channel, int input_id, uint8_t button_number)
	: ButtonBase(channel, input_id, button_number)
{
}

void MomentaryButton::state_changed(uint8_t current_state) 
{
	if(current_state == HIGH)
		SER_PRINTLN("BUTTON PRESSED");
	else
		SER_PRINTLN("BUTTON RELEASED");

	SER_PRINTLN(button_number_);
	SER_PRINTLN(current_state);
	joystick_->setButton(button_number_, current_state);
	digitalWrite(monitor_led, current_state);

}


