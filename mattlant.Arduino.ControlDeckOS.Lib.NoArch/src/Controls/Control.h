// Control.h

#ifndef _CONTROL_h
#define _CONTROL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "../Devices/InputDevice.h"
#include "../Devices/OutputDevice.h"
#include "../OS/KernelTask.h"

class Control : public KernelTaskBase
{
 protected:
	bool isSetup = false;
	InputDevice* input_device_;
	OutputDevice* output_device_;


 public:
	Control(InputDevice* input_device, OutputDevice* output_device, int sampling_interval);

	virtual ~Control() = default;

	virtual void setup_impl();

	void setup();

	virtual void process();

protected:
	TaskExecutionResult execute_impl(int resume_stage = 0) override;
};

#endif

