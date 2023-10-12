// 
// 
// 

#include "PulseOutputTask.h"
#include "../OS/KernelCommon.h"

TaskExecutionResult PulseOutputTask::execute_impl(int resume_stage)
{
	STAGED_PROCESS_BEGIN(resume_stage)

	STAGE(0)
	output_device_->write(channel_, HIGH);
	RESUME_AT_STAGE_IN_TICKS(1, interval)

	STAGE(1)
	output_device_->write(channel_, LOW);

	STAGED_PROCESS_END()
}
