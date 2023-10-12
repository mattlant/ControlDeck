// 
// 
// 

#include "ButtonBase.h"
#include "../util.h"


void ButtonBase::state_changed(uint8_t current_state)
{
}

ButtonBase::ButtonBase(InputDevice* input_device, int input_id, OutputDevice* output_device, int output_id, int sampling_interval):
	ButtonBase(nullptr, input_device, input_id, output_device, output_id, sampling_interval)
{
}

ButtonBase::ButtonBase(const char* name, InputDevice* input_device, int input_id, OutputDevice* output_device,
                       int output_id, int sampling_interval): Control(input_device, output_device, sampling_interval), 
                                       input_id_(input_id),
                                       output_id_(output_id),
                                       name_(name)

{
}


void ButtonBase::setup_impl()
{

		if(input_device_ != nullptr)
			input_device_->begin();
		if(output_device_ != nullptr)
			output_device_->begin();
		isSetup = true;
}

void ButtonBase::process()
{
	uint8_t current_state = input_device_->read(input_id_);
	if (negate_state_) current_state = !current_state;

	//DBG_PRINTLN("BUTTON_PROC");
	if (last_input_state_ != current_state)
	{
		DBG_PRINT("ButtonBase.Process:State Changed, input_id=");
		DBG_PRINT(input_id_);
		DBG_PRINT("State=");
		DBG_PRINTLN(current_state == HIGH ? "ON" : "OFF");

		this->state_changed(current_state);
		last_input_state_ = current_state;
	}
}

void ButtonBase::set_negate_state_(bool negate)
{
	negate_state_ = negate;
}
