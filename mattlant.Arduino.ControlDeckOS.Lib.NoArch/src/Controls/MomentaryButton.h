// Button.h

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "ButtonBase.h"


class MomentaryButton : public ButtonBase
{
public:
	MomentaryButton(InputDevice* channel, int input_id, OutputDevice* output_channel, int output_id, int sampling_interval = 10);
	MomentaryButton(const char* name, InputDevice* channel, int input_id, OutputDevice* output_channel, int output_id, int sampling_interval = 10);

protected:
	void state_changed(uint8_t current_state) override;

};


#endif	

