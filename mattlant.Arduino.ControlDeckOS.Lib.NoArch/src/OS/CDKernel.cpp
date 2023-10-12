#include "CDKernel.h"


#include "../util.h"

void CDKernel::setup()
{
	//Change to a Setup class that can be injected
}

void CDKernel::add_task(uint8_t priority, KernelTaskBase* task, bool immediate)
{
	if (immediate)
		task->next_execution_time = 0;
	else
		task->next_execution_time = get_ticks() + task->interval;


	switch (priority)
	{
	case KERNEL_P_CRITICAL:
		critical_tasks_.append(task);
		break;
	case KERNEL_P_MEDIUM:
		medium_tasks_.append(task);
		break;
	case KERNEL_P_LOW:
		low_tasks_.append(task);
		break;
	case KERNEL_P_POST:
		post_tasks_.append(task);
		break;
	default:
		// Handle invalid priority
		break;
	}
}


CDKernel::CDKernel(const GetTicksFunc func, const DelayFunc delay_func,
               const unsigned long runloop_exec_time_max = MAX_EXEC_TIME,
               const unsigned long runloop_exec_time_min = MIN_EXEC_TIME)
	: runloop_exec_time_max_(runloop_exec_time_max),
	  runloop_exec_time_min_(runloop_exec_time_min), get_ticks(func), system_delay(delay_func)

{
}


void CDKernel::set_get_tick_function(const GetTicksFunc func)
{
	get_ticks = func;
}

void CDKernel::set_delay_function(const DelayFunc func)
{
	system_delay = func;
}

void CDKernel::set_exec_limits(const unsigned long runloop_exec_time_max, const unsigned long runloop_exec_time_min)
{
	runloop_exec_time_min_ = runloop_exec_time_min;
	runloop_exec_time_max_ = runloop_exec_time_max;
}

unsigned long CDKernel::exec_tasks(LinkedList& task_list, const bool use_limit, const int at_least)
{
	if (use_limit && is_over_exec_limit() && at_least == 0)
		return 0;

	int tasks_executed_counter = 0;

	const auto start_ticks = get_ticks();
	auto list_iter = task_list.get_iterator();
	while (list_iter.move_next())
	{

		KernelTaskBase* task = static_cast<KernelTaskBase*>(list_iter.get_current_item());
		if (task && is_task_ready_to_execute(task))
		{
			//EXECUTION PHASE
			if (task->last_execution_status.result == TaskExecutionResult::RESUME)
			{
				task->execute(task->last_execution_status.data.resume.stage);
			}
			else
			{
				task->execute();
			}
			tasks_executed_counter++;


			//RESULT PROCESSING PHASE
			if (task->last_execution_status.result == TaskExecutionResult::ADD_TASK 
				&& task->last_execution_status.data.new_task.task != nullptr)
			{
				//TODO: Setting priority properly
				this->add_task(KERNEL_P_MEDIUM, static_cast<KernelTaskBase*>(task->last_execution_status.data.new_task.task),
				               task->last_execution_status.data.new_task.immediate);
				task->last_execution_status.data.new_task.task = nullptr;
			}

			if (task->last_execution_status.result == TaskExecutionResult::RESUME)
			{
				task->next_execution_time = get_ticks() + task->last_execution_status.data.resume.ticks;
			}
			else
			{
				if (task->is_one_time())
				{
					//TODO: REMOVE TASK. using disabled workaround for now
					list_iter.remove_current(true);
				}
				else
				{
					task->next_execution_time = get_ticks() + task->interval;
				}
			}
		}

		if (use_limit && is_over_exec_limit())
		{
			if (tasks_executed_counter >= at_least)
			{
				//We do this so we start with next task on next cycle
				if (list_iter.has_next())
					task_list.set_head_to_next(list_iter.get_current_item());


				break;
			}
		}
	}

	return get_ticks() - start_ticks;
}

bool CDKernel::is_task_ready_to_execute(const KernelTaskBase* task) const
{
	return !task->is_disabled && get_ticks() >= task->next_execution_time;
}


bool CDKernel::is_over_exec_limit() const
{
	return get_runloop_exec_time() >= runloop_exec_time_max_;
}

bool CDKernel::is_over_exec_min() const
{
	return get_runloop_exec_time() >= runloop_exec_time_min_;
}

unsigned long CDKernel::get_runloop_exec_time() const
{
	return get_ticks() - iteration_start_ticks_;
}

uint8_t CDKernel::get_kernel_utilization() const
{
	const auto current_ticks = get_ticks();
	const auto running_for_ticks = current_ticks - start_run_ticks_;

	const auto ticks_utilized = running_for_ticks - total_delayed_ticks_;
	return static_cast<uint8_t>(round(
		(static_cast<float>(ticks_utilized) / static_cast<float>(running_for_ticks)) * 100));
}

void CDKernel::delay_ticks(const unsigned long ticks)
{
	total_delayed_ticks_ += ticks;
	system_delay(ticks);
}

void CDKernel::idle()
{
	last_loop_idle_time = 0;
	const int loop_time = get_ticks() - iteration_start_ticks_;
	if (is_over_exec_min())
		return;

	unsigned long diff = runloop_exec_time_min_ - loop_time;
	//DBG_PRINT("EmKernel: Finished loop under min loop exec time. Will idle for ms: ");
	//DBG_PRINTLN(diff);
	last_loop_idle_time = diff;
	if (diff > 0)
	{
		//last_loop_idle_time = diff;
		this->delay_ticks(diff);
	}
}

void CDKernel::run()
{
	start_run_ticks_ = get_ticks();
	DBG_PRINTLN("EmKernel.run() start");
	while (true)
	{
		//Need to add this as a task
		loop_counter.process();

		iteration_start_ticks_ = get_ticks();
		exec_tasks(critical_tasks_, false);
		exec_tasks(medium_tasks_, true, 1);
		exec_tasks(low_tasks_, true, 0);
		exec_tasks(post_tasks_, false);
		last_loop_exec_time = get_ticks() - iteration_start_ticks_;

		idle();
	}
	DBG_PRINTLN("EmKernel.run() end");
}

unsigned long CDKernel::get_loop_count()
{
	return loop_counter.get_loops_total();
}

#ifdef ARDUINO
#if EMK_HIGH_PRECISION_SCHEDULING == 1
EmKernel Kernel = CDKernel(micros, delayMicroseconds );
#else
CDKernel Kernel = CDKernel(millis, delay, EMK_DEFAULT_MAX_EXEC_TIME, EMK_DEFAULT_MIN_EXEC_TIME);
#endif

#else
  // Non-Arduino code here
#endif
