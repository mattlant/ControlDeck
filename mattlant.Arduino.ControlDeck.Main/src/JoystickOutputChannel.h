// JoystickOutputChannel.h

#ifndef HIDJOYSTICKOUTPUTCHANNEL_h
#define HIDJOYSTICKOUTPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Joystick.h>

#include "OutputChannel.h"

enum JoystickButtons
{
	HAT = 1000,
	XAxis = 1001,
	YAxis = 1002,
	ZAxis = 1003
};

class JoystickOutputChannel : public OutputChannel
{
private:

public:
	JoystickOutputChannel(uint8_t hid_report_id, int output_ids[], int output_count)
		: OutputChannel(output_ids, output_count)
	{
		//joy_ref = Joystick_(hid_report_id,JOYSTICK_TYPE_JOYSTICK, 32, 0,
		//                    false, false, false, false, false, false,
		//                    false, false, false, false, false);

		//using 'new' because this will never actually require removal while in operation
		joystick_ = new Joystick_(hid_report_id,JOYSTICK_TYPE_JOYSTICK, 32, 0,
		                          false, false, false, false, false, false,
		                          false, false, false, false, false);
	}

	~JoystickOutputChannel() = default;

	void begin() override
	{
		joystick_->begin();
	}

	void write(int button_id, int value) override;

protected:
	Joystick_* joystick_;
};

#endif
