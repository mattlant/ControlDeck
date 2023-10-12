#include "KernelTask.h"

KernelTaskBase::KernelTaskBase(bool is_one_time, unsigned interval): interval(interval), is_one_time_(is_one_time)
{
}

TaskExecutionResult KernelTaskBase::execute(int resume_stage)
{
	last_execution_status = execute_impl(resume_stage);
	return last_execution_status;
}

bool KernelTaskBase::is_one_time() const
{
	return is_one_time_;
}

TaskExecutionResult KernelTaskBase::resume_impl()
{
	return TaskExecutionResult{TaskExecutionResult::COMPLETE};
}






