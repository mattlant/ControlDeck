#ifndef EMB_KERNEL_TASK_H
#define EMB_KERNEL_TASK_H
#include "KernelCommon.h"
#include "../LinkedList.h"


class KernelTaskBase : public LinkedListItemBase
{
	uint16_t id_ = 0;

public:
	virtual ~KernelTaskBase() = default;
	KernelTaskBase(bool is_one_time, unsigned int interval);

	unsigned long next_execution_time = 0;
	TaskExecutionResult last_execution_status = TaskExecutionResult();
	bool is_disabled = false;
	unsigned int interval;
	bool is_one_time_;

	TaskExecutionResult execute(int resume_stage = 0);

	virtual bool is_one_time() const;

protected:
	virtual TaskExecutionResult execute_impl(int resume_stage = 0) = 0;
	virtual TaskExecutionResult resume_impl();
};


class KernelTask : public KernelTaskBase
{

protected:
	TaskResumeFunc resume_func_ = nullptr;
	TaskFunc func_; // The function to call

public:
	KernelTask(TaskFunc func, TaskResumeFunc resume_func = nullptr, bool is_one_time = false, unsigned interval = 1)
		: KernelTaskBase(is_one_time, interval),
		  resume_func_(resume_func),
		  func_(func)
	{
	}
	KernelTask(TaskFunc func, bool is_one_time, unsigned interval)
		: KernelTaskBase(is_one_time, interval),
		  func_(func)
	{
	}

	TaskExecutionResult execute_impl(int resume_stage = 0) override;
};

inline TaskExecutionResult KernelTask::execute_impl(int resume_stage)
{
	return func_();
}



template <typename T, typename FuncType>
class KernelParamTask : public KernelTaskBase
{
private:
	TaskResumeFunc resume_func_ = nullptr;
	FuncType func_; // The function to call
	T param_; // The parameter to pass

public:
	KernelParamTask(FuncType func, T param, TaskResumeFunc resume_func, bool is_one_time, unsigned interval)
		: KernelTaskBase(is_one_time, interval),
		  resume_func_(resume_func),
		  func_(func),
		  param_(param)
	{
	}

	KernelParamTask(FuncType func, T param, bool is_one_time, unsigned interval)
		: KernelTaskBase(is_one_time, interval),
		  func_(func),
		  param_(param)
	{
	}

	TaskExecutionResult execute_impl(int resume_stage = 0) override;
};

template <typename T, typename FuncType>
TaskExecutionResult KernelParamTask<T, FuncType>::execute_impl(int resume_stage)
{
	return func_(param_);
}



#endif
