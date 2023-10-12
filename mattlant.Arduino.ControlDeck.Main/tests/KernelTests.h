// KernelTests.h

#ifndef _KERNELTESTS_h
#define _KERNELTESTS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "../src/Sketch.h"
#include "../src/OS/CDKernel.h"


class StageCounterTask : public KernelTaskBase
{
public:
	StageCounterTask(bool is_one_time, unsigned interval)
		: KernelTaskBase(is_one_time, interval)
	{
	}

protected:
	TaskExecutionResult execute_impl(int stage = 0) override
	{
		STAGED_PROCESS_BEGIN(stage)
		STAGE(0)
			Serial.println("Start of staged process!");
			RESUME_AT_STAGE_IN_TICKS(1, 1000)

		STAGE(1)
			Serial.println("Stage 1");
			RESUME_AT_STAGE_IN_TICKS(2, 1000)

		STAGE(2)
			Serial.println("Stage 2");
			RESUME_AT_STAGE_IN_TICKS(3, 1000)

		STAGE(3)
			Serial.println("Stage 3");
			RESUME_AT_STAGE_IN_TICKS(4, 1000)

		STAGE(4)
			Serial.println("Stage 4, will fall through to 5");

		STAGE(5)
			Serial.println("Stage 5 direct from 4");
			RESUME_AT_STAGE_IN_TICKS(6, 1000)

		STAGE(6)
			Serial.println("End of staged process (stage 6)");

		STAGED_PROCESS_END()
	}
};

inline int slow_read(const int id)
{
	delay(5);
	return id;
}

inline void slow_write(int id, int value)
{
	delay(5);
}

class SomeLoopingTask_Blocking : public KernelTaskBase
{
public:
	SomeLoopingTask_Blocking(bool is_one_time, unsigned interval)
		: KernelTaskBase(is_one_time, interval)
	{
	}

protected:
	TaskExecutionResult execute_impl(int stage = 0) override
	{
		unsigned long start = millis();
		// Loop through a device channels, read the value, double it and write it back
		int device_channel_count = 128;
		for (int channel = 0; channel < device_channel_count; channel++)
		{
			const int new_value = slow_read(channel) * 2;
			slow_write(channel, new_value);
		}
		Serial.print("LoopTask Blocking took: ");
		Serial.println(millis() - start);
		return {TaskExecutionResult::COMPLETE};
	}
};

class SomeLoopingTask_NonBlocking : public KernelTaskBase
{
public:
	SomeLoopingTask_NonBlocking(bool is_one_time, unsigned interval)
		: KernelTaskBase(is_one_time, interval)
	{
	}

protected:
	int channel = 0;

	TaskExecutionResult execute_impl(int resume_stage = 0) override
	{
		int device_channel_count = 128;

		if (resume_stage == 0)
		{
			//first execution. Initialize state and resume next kernel cycle
			channel = 0;
			return TaskExecutionResult::Resume(1, 0);
		}

		if (resume_stage == 1)
		{
			const int new_value = slow_read(channel) * 2;
			slow_write(channel, new_value);
			channel++;

			if (channel < device_channel_count)
				return TaskExecutionResult::Resume(1, 0);
		}

		return {TaskExecutionResult::COMPLETE};
	}
};

class SomeLoopingTask_NonBlockingMacros : public KernelTaskBase
{
public:
	SomeLoopingTask_NonBlockingMacros(bool is_one_time, unsigned interval)
		: KernelTaskBase(is_one_time, interval)
	{
	}

protected:
	int channel = 0;
	unsigned long start = 0;

	TaskExecutionResult execute_impl(int resume_stage = 0) override
	{
		int device_channel_count = 128;

		LOOP_PROCESS_BEGIN({channel = 0;start = millis();}, 1)

		FOR_PROCESS_STAGE(channel < device_channel_count,channel++,
		                    {
		                    const int new_value = slow_read(channel) * 2;
		                    slow_write(channel, new_value);
		                    })

		LOOP_PROCESS_END({
				Serial.print("LoopTask Blocking took: ");
				Serial.println(millis() - start);
				})
	}
};

class KernelTestsClass : public SketchBase
{
public:
	static long critical_exec_count;
	static long med_exec_count;
	static long low_exec_count;
	static unsigned long last_printed;
	static unsigned long print_count;
	static unsigned long last_execute;

	static void flash_leds_alt(int times, int ms);
	static void flash_leds(int times, int ms);
	static TaskExecutionResult flash_once();
	static TaskExecutionResult flash_multi();
	static TaskExecutionResult flash_once_alt();
	static TaskExecutionResult red_on();
	static TaskExecutionResult red_off();
	static TaskExecutionResult gr_on();
	static TaskExecutionResult gr_off();
	static TaskExecutionResult blue_on();
	static TaskExecutionResult blue_off();
	static TaskExecutionResult yellow_on();
	static TaskExecutionResult yellow_off();
	static TaskExecutionResult delay_500();
	static TaskExecutionResult kill_check();
	static TaskExecutionResult process_pause();
	static TaskExecutionResult task_func_delay_random();
	static TaskExecutionResult inc_critical();
	static TaskExecutionResult inc_medium();
	static TaskExecutionResult inc_low();
	static TaskExecutionResult print_kernel_report();
	static TaskExecutionResult print_loop_count();
	static TaskExecutionResult task_func_interval_5000();
	static TaskExecutionResult exec_serial_diagnostics();

	void setup_blink_test_with_delays_tasks();
	void setup_blink_test_with_resume_tasks();
	static void setup_loop_countering_test_tasks();
	static TaskExecutionResult delay_incrementing();
	static TaskExecutionResult delay_1_medium();
	static TaskExecutionResult delay_1_low();
	static TaskExecutionResult preempt_test_print_report();
	static void setup_test_med_low_preemption();
	static TaskExecutionResult println_int(int value);
	static TaskExecutionResult println_char(const char* value);
	static void setup_param_passing_test();
	static void setup_param_passing_test2();
	static TaskExecutionResult inc_auto_create_task(int current_counter);
	static void setup_create_one_time_every_execution_test();
	static void setup_many_one_time_tasks();
	void setup() override;
	void loop() override;
};


#endif
