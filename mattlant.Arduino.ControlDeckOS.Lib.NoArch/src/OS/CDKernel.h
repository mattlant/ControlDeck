#ifndef EMB_KERNEL_H
#define EMB_KERNEL_H

#include <Arduino.h>

#include "KernelTask.h"
#include "../LinkedList.h"

#define MAX_TASKS 100

//Defaults. Can be changed via EmKernel ctor
#define MAX_EXEC_TIME 5
#define MIN_EXEC_TIME 1

#define LOOP_COUNTER_NUM_LOOPS_AVG_SAMPLES 5

#define KERNEL_P_CRITICAL 0
#define KERNEL_P_MEDIUM 1
#define KERNEL_P_LOW 2
#define KERNEL_P_POST 10

class LoopCounter
{
	unsigned int loops_per_sec[LOOP_COUNTER_NUM_LOOPS_AVG_SAMPLES] = {};
	unsigned long last_period_end_time = 0;
	double avg_loops_per_second = 0;
	unsigned int loop_index = 0;
	unsigned int loops_this_second_counter = 0;

	unsigned long loops_total;

public:
	void process()
	{
		loops_total++;
		loops_this_second_counter++;
		const unsigned long current_time = millis();
		if (current_time - last_period_end_time > 1000)
		{
			//store loops
			loops_per_sec[loop_index++] = loops_this_second_counter;
			loops_this_second_counter = 0;
			last_period_end_time = current_time;
			if (loop_index == LOOP_COUNTER_NUM_LOOPS_AVG_SAMPLES) loop_index = 0;

			unsigned int total_loops = 0;
			for (int i = 0; i < LOOP_COUNTER_NUM_LOOPS_AVG_SAMPLES; i++)
				total_loops += loops_per_sec[i];

			avg_loops_per_second = static_cast<float>(total_loops) / LOOP_COUNTER_NUM_LOOPS_AVG_SAMPLES;
		}
	}

	double get_average_loops_per_second() const
	{
		return avg_loops_per_second;
	}

	unsigned int get_loops_total() const
	{
		return loops_total;
	}
};

typedef unsigned long (*GetTicksFunc)();
typedef void (*DelayFunc)(unsigned long);


class CDKernel
{
public:
	CDKernel(GetTicksFunc func, DelayFunc delay_func, unsigned long runloop_exec_time_max,
	       unsigned long runloop_exec_time_min);

	void set_get_tick_function(GetTicksFunc func);
	void set_delay_function(DelayFunc func);
	void set_exec_limits(unsigned long runloop_exec_time_max, unsigned long runloop_exec_time_min);
	unsigned long last_loop_exec_time;
	unsigned long last_loop_idle_time;

private:
	LinkedList critical_tasks_ = LinkedList(); // Priority 0
	LinkedList medium_tasks_ = LinkedList(); // Priority 1
	LinkedList low_tasks_ = LinkedList(); // Priority 2
	LinkedList post_tasks_ = LinkedList(); // Priority 10 (CHANGE THIS)

	unsigned long iteration_start_ticks_ = 0;
	unsigned long runloop_exec_time_max_;
	unsigned long runloop_exec_time_min_;
	GetTicksFunc get_ticks;
	DelayFunc system_delay;
	unsigned long total_delayed_ticks_;
	unsigned long start_run_ticks_;

	unsigned long exec_tasks(LinkedList& task_list, bool use_limit = false, int at_least = 1);
	bool is_task_ready_to_execute(const KernelTaskBase* task) const;
	bool is_over_exec_limit() const;
	bool is_over_exec_min() const;
	unsigned long get_runloop_exec_time() const;
	void idle();

public:
	void setup();
	void add_task(uint8_t priority, KernelTaskBase* task, bool immediate = false);
	void run();
	unsigned long get_loop_count();
	uint8_t get_kernel_utilization() const;
	void delay_ticks(unsigned long ticks);

	LoopCounter loop_counter = LoopCounter();

private:
};

extern CDKernel Kernel;

#endif
