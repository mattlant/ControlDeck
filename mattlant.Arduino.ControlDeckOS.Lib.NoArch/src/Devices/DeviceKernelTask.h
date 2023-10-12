// DeviceKernelTask.h

#ifndef _DEVICEKERNELTASK_h
#define _DEVICEKERNELTASK_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "IoDevice.h"
#include "../OS/KernelTask.h"

class IoDeviceKernelTask : public KernelTaskBase
{
public:
	IoDeviceKernelTask(unsigned interval, IoDevice* io_device)
		: KernelTaskBase(false, interval), io_device_(io_device)
	{
	}


protected:
	TaskExecutionResult execute_impl(int resume_stage = 0) override
	{
		io_device_->process();
		return TASK_RESULT_COMPLETE;
	}

public:
	IoDevice* io_device_;
};


#endif

