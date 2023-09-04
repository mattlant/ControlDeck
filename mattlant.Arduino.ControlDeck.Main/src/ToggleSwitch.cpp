#include "ToggleSwitch.h"
#include "util.h"


ToggleSwitch::ToggleSwitch(uint8_t input_pin, uint8_t button_number, uint8_t led_pin):
	ButtonBase(input_pin, button_number), led_pin_(led_pin)

{
	if (led_pin > 0)
		use_led_ = true;
}


void ToggleSwitch::update_led() const
{
	digitalWrite(led_pin_, last_input_state_);
}

void ToggleSwitch::setup() 
{
	ButtonBase::setup();

	SER_PRINT("TOGGLE::SETUP BUTTONNUM=");
	SER_PRINTLN(button_number_);

	last_input_state_ = !digitalRead(input_pin_);
	if (use_led_)
		update_led();
}

void ToggleSwitch::process() 
{
	process_button_press();
	if (is_pressing_button)
		return;

	ButtonBase::process();

}

void ToggleSwitch::state_changed(uint8_t current_state)
{
	update_led();
	start_button_press();
}


void ToggleSwitch::start_button_press()
{
	if (is_pressing_button)
		return;

	SER_PRINT("startbuttonpress");

	is_pressing_button = true;
	start_press_millis_ = millis();
	joystick_->setButton(button_number_, HIGH);
	digitalWrite(8, HIGH);
}

void ToggleSwitch::process_button_press()
{
	if (!is_pressing_button)
		return;


	if (millis() - start_press_millis_ >= toggle_switch_button_press_timespan)
	{
		SER_PRINT("elapmill=");
		SER_PRINT(millis() - start_press_millis_);
		SER_PRINTLN();
		SER_PRINTLN("endbuttonpress");

		joystick_->setButton(button_number_, LOW);
		digitalWrite(8, LOW);

		is_pressing_button = false;
	}
}
