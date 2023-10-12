// Button.h

#ifndef TOGGLE_SWITCH_h
#define TOGGLE_SWITCH_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ButtonBase.h"

constexpr int toggle_switch_button_press_timespan = 100;


class LatchToMomentary : public ButtonBase
{
public:
	LatchToMomentary(InputDevice* channel, int input_id, OutputDevice* output_channel, int output_id, int sampling_interval = 10);
	void setup_impl() override;
	void process() override;

protected:

	//void update_time();
	void state_changed(uint8_t current_state) override;
};


#endif
