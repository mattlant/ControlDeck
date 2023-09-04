// ButtonBase.h

#ifndef BUTTONBASE_h
#define BUTTONBASE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <Joystick.h>

#include "InputChannel.h"
#include "OutputChannel.h"

class ButtonBase
{
public:
	virtual ~ButtonBase() = default;
	ButtonBase(InputChannel* channel, int input_id, OutputChannel* output_channel, int output_id);
	virtual void setup();
	virtual void process();
	void set_negate_input(bool negate);

protected:
	InputChannel* input_channel_;
	int input_id_;
	OutputChannel* output_channel_;
	int output_id_;

	uint8_t last_input_state_ = 0;
	bool negate_input = false;

	virtual void state_changed(uint8_t current_state);
};


#endif
