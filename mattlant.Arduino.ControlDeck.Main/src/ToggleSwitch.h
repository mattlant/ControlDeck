// Button.h

#ifndef _TOGGLE_SWITCH_h
#define _TOGGLE_SWITCH_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Joystick.h"
#include "ButtonBase.h"

constexpr int toggle_switch_button_press_timespan = 100;


class ToggleSwitch : public ButtonBase
{
public:
	ToggleSwitch(InputChannel* channel, int input_id, OutputChannel* output_channel, int output_id, uint8_t led_pin = 0);
	void setup() override;
	void process() override;

protected:
	uint8_t led_pin_;
	bool use_led_ = false;
	bool is_pressing_button = false;
	unsigned long start_press_millis_ = 0;


	void start_button_press();
	void process_button_press();
	//void update_time();
	void update_led() const;
	void state_changed(uint8_t current_state) override;


};


#endif
