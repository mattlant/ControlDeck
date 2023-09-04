// Button.h

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Joystick.h"
#include "ButtonBase.h"


class MomentaryButton : public ButtonBase
{
public:
	MomentaryButton(InputChannel* channel, int input_id, uint8_t button_number);

protected:
	void state_changed(uint8_t current_state) override;


};


#endif	

