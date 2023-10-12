// ButtonBase.h

#ifndef BUTTONBASE_h
#define BUTTONBASE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Control.h"
#include "../Devices/InputDevice.h"
#include "../Devices/OutputDevice.h"

class ButtonBase : public Control
{

public:
	void setup_impl() override;
	void process() override;
	void set_negate_state_(bool negate);

protected:
	int input_id_;
	int output_id_;

	uint8_t last_input_state_ = 0;
	bool negate_state_ = false;
	const char* name_;

	virtual void state_changed(uint8_t current_state);

		ButtonBase(InputDevice* input_device, int input_id, OutputDevice* output_device, int output_id,
	           int sampling_interval);
	ButtonBase(const char* name, InputDevice* input_device, int input_id, OutputDevice* output_device, int output_id,
	           int sampling_interval);

};


#endif
