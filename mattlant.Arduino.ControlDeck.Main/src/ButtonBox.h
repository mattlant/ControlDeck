// ButtonBox.h

#ifndef _BUTTONBOX_h
#define _BUTTONBOX_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "MomentaryButton.h"
#include "ButtonBase.h"
#include "ToggleSwitch.h"

class ButtonBox
{
protected:
	Joystick_ buttonBox_internal = Joystick_(0x01,JOYSTICK_TYPE_JOYSTICK, 32, 0,
	                                         false, false, false, false, false, false,
	                                         false, false, false, false, false);

	Joystick_* joystick_ = &buttonBox_internal;

	ButtonBase** buttons_;
	int button_count_;
	uint8_t loop_delay_;

public:
	ButtonBox(ButtonBase* buttons[], int button_count, uint8_t loop_delay);

	virtual void setup();
	virtual void process();
};


#endif
