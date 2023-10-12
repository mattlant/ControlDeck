#include "LatchToMomentary.h"
#include "../util.h"


LatchToMomentary::LatchToMomentary(InputDevice* channel, int input_id, OutputDevice* output_channel, int output_id,
                                   int sampling_interval)
	: ButtonBase(channel, input_id, output_channel, output_id, sampling_interval)
{
}

void LatchToMomentary::setup_impl()
{
	ButtonBase::setup_impl();

	DBG_PRINT("TOGGLE::SETUP BUTTONNUM=");
	DBG_PRINTLN(output_id_);

	last_input_state_ = input_device_->read(input_id_);
}

void LatchToMomentary::process()
{
	//process_button_press();
	//if (is_pressing_button)
	//	return;

	ButtonBase::process();
}

void LatchToMomentary::state_changed(uint8_t current_state)
{
	output_device_->pulse(output_id_, 33);
}

