// 
// 
// 

#include "JoystickOutputChannel.h"

#include "util.h"


void JoystickOutputChannel::write(int button_id, int value) const
{
	if (button_id < 1000)
	{
		SER_PRINT("CHANNEL_JOYBUTTON:");
		SER_PRINT(button_id);
		SER_PRINT("STATE:");
		SER_PRINT(value);
		joystick_->setButton(button_id, value);
	}
	else
	{
		switch (button_id)
		{
		case JoystickButtons::HAT:
			joystick_->setHatSwitch(0, value);
			break;
		case JoystickButtons::XAxis:
			joystick_->setXAxis(value);
			break;
		case JoystickButtons::YAxis:
			joystick_->setYAxis(value);
			break;
		case JoystickButtons::ZAxis:
			joystick_->setZAxis(value);
			break;
		}
		//TODO: Add more joystick outputs
	}
}
