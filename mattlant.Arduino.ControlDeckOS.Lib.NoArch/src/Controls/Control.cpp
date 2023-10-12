// 
// 
// 

#include "Control.h"


Control::Control(InputDevice* input_device, OutputDevice* output_device, int sampling_interval): KernelTaskBase(false, sampling_interval), input_device_(input_device),
                                                                          output_device_(output_device)
{
}

void Control::setup_impl()
{
}

void Control::setup()
{
	if(isSetup)
		return;
	isSetup = true;
	setup_impl();
}

void Control::process()
{
}

TaskExecutionResult Control::execute_impl(int resume_stage)
{
	last_execution_status = {};
	process();
	return last_execution_status;
}


