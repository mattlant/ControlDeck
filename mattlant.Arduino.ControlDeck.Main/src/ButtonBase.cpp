// 
// 
// 

#include "ButtonBase.h"
#include "util.h"



void ButtonBase::state_changed(uint8_t current_state)
{
}

ButtonBase::ButtonBase(InputChannel* channel, int input_id, OutputChannel* output_channel, int output_id):
	input_channel_(channel),
	input_id_(input_id),
	output_channel_(output_channel),
	output_id_(output_id)
{
}

void ButtonBase::setup()
{
}

void ButtonBase::process()
{
	const uint8_t current_state = input_channel_->read(input_id_);
	//SER_PRINTLN("BUTTON_PROC");
	if (last_input_state_ != current_state)
	{
		SER_PRINT("ButtonBase.Process:State Changed=");
		SER_PRINTLN(current_state == HIGH ? "ON" : "OFF");

		this->state_changed(current_state);
		last_input_state_ = current_state;
	}
}
