// 
// 
// 

// ReSharper disable CppClangTidyBugproneNarrowingConversions

#include "JoystickOutputDevice.h"

#include "../util.h"


JoystickOutputDevice::JoystickOutputDevice(uint8_t hid_report_id, byte button_count, bool use_x_axis, bool use_y_axis,
                                           bool use_z_axis): OutputDevice(), 
                                                             use_x_axis_(use_x_axis), use_y_axis_(use_y_axis),
                                                             use_z_axis_(use_z_axis), hid_report_id_(hid_report_id)
{
	//joy_ref = Joystick_(hid_report_id,JOYSTICK_TYPE_JOYSTICK, 32, 0,
	//                    false, false, false, false, false, false,
	//                    false, false, false, false, false);
	channel_count_ = button_count;
	channel_map_ = new byte[button_count];
	for (int i = 0; i < button_count; i++)
		channel_map_[i] = i;

	button_channel_map_ = channel_map_;

	joystick_ = new Joystick_(hid_report_id_,JOYSTICK_TYPE_JOYSTICK, channel_count_, 0,
                          use_x_axis_, use_y_axis_, use_z_axis_, false, false, false,
                          false, false, false, false, false);


	joystick_->begin();



	//using 'new' because this will never actually require removal while in operation
}

void JoystickOutputDevice::begin_()
{
	DBG_PRINTLN("Joystick Starting");
	if(use_x_axis_)
		joystick_->setXAxisRange(axis1_range_.x_min, axis1_range_.x_max);
	if(use_y_axis_)
		joystick_->setXAxisRange(axis1_range_.y_min, axis1_range_.y_max);
	if(use_z_axis_)
		joystick_->setXAxisRange(axis1_range_.z_min, axis1_range_.z_max);


	//joystick_->sendState();
}

void JoystickOutputDevice::write(byte button_id, int value)
{
	DBG_PRINT("CHANNEL_JOY:");
	DBG_PRINT(button_id);
	DBG_PRINT("VALUE:");
	DBG_PRINTLN(value);
	if (button_id < 128)
	{
		joystick_->setButton(button_id, value);

	}
	else
	{
		switch (button_id)
		{
		case HAT:
			joystick_->setHatSwitch(0, value);
			break;
		case XAxis:
			if(use_x_axis_)
				joystick_->setXAxis(value);
			break;
		case YAxis:
			if(use_y_axis_)
				joystick_->setYAxis(value);
			break;
		case ZAxis:
			if(use_z_axis_)
				joystick_->setZAxis(value);
			break;
		default:
			break;
		}
		//TODO: Add more joystick outputs
	}
}

void JoystickOutputDevice::setup_axis(byte axis_number, int min_range, int max_range)
{
	if(axis_number == XAxis)
	{
		axis1_range_.x_min = min_range;
		axis1_range_.x_max = max_range;
	}
	if(axis_number == YAxis)
	{
		axis1_range_.y_min = min_range;
		axis1_range_.y_max = max_range;
	}
	if(axis_number == ZAxis)
	{
		axis1_range_.z_min = min_range;
		axis1_range_.z_max = max_range;
	}
}
