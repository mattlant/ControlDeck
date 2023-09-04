// 
// 
// 

// ReSharper disable CppClangTidyBugproneNarrowingConversions
#include "JoystickOutputChannel.h"

#include "util.h"


void JoystickOutputChannel::write(int button_id, int value) 
{
	if (button_id < 0xFF)
	{
		SER_PRINT("CHANNEL_JOYBUTTON:");
		SER_PRINT(button_id);
		SER_PRINT("STATE:");
		SER_PRINTLN(value);
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
		default:
			break;
		}
		//TODO: Add more joystick outputs
	}
}
