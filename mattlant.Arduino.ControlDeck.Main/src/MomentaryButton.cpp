// 
// 
// 

#include "util.h"
#include "MomentaryButton.h"
#include "ButtonBase.h"




MomentaryButton::MomentaryButton(uint8_t input_pin, int button_number): ButtonBase(input_pin, button_number)
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


