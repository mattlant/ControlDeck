// PulseOutputTask.h

#ifndef _PULSEOUTPUTTASK_h
#define _PULSEOUTPUTTASK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "../Devices/OutputDevice.h"
#include "../OS/KernelCommon.h"
#include "../OS/KernelTask.h"

class PulseOutputTask : public KernelTaskBase
{
public:
	PulseOutputTask(OutputDevice* output_device, byte channel, unsigned int pulse_length)
		: KernelTaskBase(true, pulse_length), output_device_(output_device), channel_(channel)
	{
	}

protected:
	TaskExecutionResult execute_impl(int resume_stage = 0) override;

public:
	OutputDevice* output_device_;
	byte channel_;
};


#endif

