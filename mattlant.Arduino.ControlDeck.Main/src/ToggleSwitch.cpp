#include "ToggleSwitch.h"
#include "util.h"


ToggleSwitch::ToggleSwitch(InputChannel* channel, int input_id, OutputChannel* output_channel, int output_id,
                           uint8_t led_pin)
	: ButtonBase(channel, input_id, output_channel, output_id), led_pin_(led_pin)
{
	if (led_pin > 0)
		use_led_ = true;
}

void ToggleSwitch::update_led() const
{
	if (use_led_)
		digitalWrite(led_pin_, last_input_state_);
}

void ToggleSwitch::setup()
{
	ButtonBase::setup();

	SER_PRINT("TOGGLE::SETUP BUTTONNUM=");
	SER_PRINTLN(output_id_);

	last_input_state_ = input_channel_->read(input_id_);
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

	SER_PRINTLN("ToggleSwitch::start button press");

	is_pressing_button = true;
	start_press_millis_ = millis();
	output_channel_->write(output_id_, HIGH);
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
		SER_PRINTLN("ToggleSwitch::end button press");

		output_channel_->write(output_id_, LOW);
		digitalWrite(8, LOW);

		is_pressing_button = false;
	}
}
