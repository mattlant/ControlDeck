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
	ButtonBase** buttons_;
	int button_count_;
	uint8_t loop_delay_;

public:
	ButtonBox(ButtonBase* buttons[], int button_count, uint8_t loop_delay);

	virtual void setup();
	virtual void process();
};


#endif
