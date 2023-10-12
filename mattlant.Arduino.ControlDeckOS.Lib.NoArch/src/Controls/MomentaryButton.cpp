// 
// 
// 

#include "../util.h"
#include "MomentaryButton.h"
#include "ButtonBase.h"

MomentaryButton::MomentaryButton(InputDevice* channel, int input_id, OutputDevice* output_channel, int output_id, int sampling_interval)
	: ButtonBase(channel, input_id, output_channel, output_id, sampling_interval)
{
}

MomentaryButton::MomentaryButton(const char* name, InputDevice* channel, int input_id, OutputDevice* output_channel,
	int output_id, int sampling_interval): ButtonBase(name, channel, input_id, output_channel, output_id, sampling_interval)
{
}

void MomentaryButton::state_changed(uint8_t current_state) 
{
	output_device_->write(output_id_, current_state);
}


