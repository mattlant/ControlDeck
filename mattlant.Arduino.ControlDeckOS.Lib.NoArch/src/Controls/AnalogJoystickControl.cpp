// 
// 
// 

#include "AnalogJoystickControl.h"

void AnalogJoystickControl::setup_impl()
{
	input_device_->set_to_analog();
}

void AnalogJoystickControl::process()
{
	const int x = input_device_->read(x_input_channel_);
	const int y = input_device_->read(y_input_channel_);

	if(x != x_value_ || y != y_value_)
	{
		const int x_diff = abs(x - x_value_);
		const int y_diff = abs(y - y_value_);
		if(x_diff + y_diff > AXIS_SENSITIVITY)
		{
			x_value_ = x;
			y_value_ = y;
			//TRIGGER OUTPUT
			output_device_->write(x_output_channel_, x_value_);
			output_device_->write(y_output_channel_, y_value_);
		}
	}

}
