// 
// 
// 

#include "util.h"
#include "MomentaryButton.h"
#include "ButtonBase.h"
#include "OutputChannel.h"

MomentaryButton::MomentaryButton(InputChannel* channel, int input_id, OutputChannel* output_channel, int output_id)
	: ButtonBase(channel, input_id, output_channel, output_id)
{
}

void MomentaryButton::state_changed(uint8_t current_state) 
{
	output_channel_->write(output_id_, current_state);
}
