// 
// 
// 

#include "KernelTests.h"
#ifndef ARDUINO_SIM
#include "../src/Serial/SerialDiagnostics.h"
#endif
#include "../src/util.h"
#include "../src/OS/CDKernel.h"

#define RED_LED_PIN 4
#define YELLOW_LED_PIN 5
#define BLUE_LED_PIN 6
#define GREEN_LED_PIN 7
#define KILL_SWITCH_PIN 9
#define PAUSE_BUTTON_PIN 10

long KernelTestsClass::critical_exec_count = 0;
long KernelTestsClass::med_exec_count = 0;
long KernelTestsClass::low_exec_count = 0;
unsigned long KernelTestsClass::last_printed = 0;
unsigned long KernelTestsClass::print_count = 0;
unsigned long KernelTestsClass::last_execute = 0;

void println(const char* text)
{
	Serial.println(text);
}

void println_value(const char* text, long value)
{
	Serial.print(text);
	Serial.println(value);
}


void KernelTestsClass::flash_leds_alt(int times, int ms)
{
	for (int i = 0; i < times; i++)
	{
		digitalWrite(RED_LED_PIN, HIGH);
		digitalWrite(GREEN_LED_PIN, LOW);
		delay(ms);
		digitalWrite(RED_LED_PIN, LOW);
		digitalWrite(GREEN_LED_PIN, HIGH);
		delay(ms);
	}
}

void KernelTestsClass::flash_leds(int times, int ms)
{
	for (int i = 0; i < times; i++)
	{
		digitalWrite(RED_LED_PIN, HIGH);
		digitalWrite(GREEN_LED_PIN, HIGH);
		delay(ms);
		digitalWrite(RED_LED_PIN, LOW);
		digitalWrite(GREEN_LED_PIN, LOW);
		delay(ms);
	}
}

unsigned long flash_ticks;

TaskExecutionResult flash_leds_r()
{
	digitalWrite(GREEN_LED_PIN, HIGH);
	println_value("LED ON: ticks since last: ", millis() - flash_ticks);
	flash_ticks = millis();
	TaskExecutionResult result;
	result.result = TaskExecutionResult::RESUME;
	result.data.resume.ticks = 500;
	return result;
}

TaskExecutionResult flash_leds_r_resume(uint8_t resume_key)
{
	digitalWrite(GREEN_LED_PIN, LOW);
	println_value("LED OFF: ticks since last: ", millis() - flash_ticks);
	flash_ticks = millis();
	return {};
}

TaskExecutionResult KernelTestsClass::flash_once()
{
	flash_leds(1, 50);
	return {};
}

TaskExecutionResult KernelTestsClass::flash_multi()
{
	flash_leds(100, 50);
	return {};
}

TaskExecutionResult KernelTestsClass::flash_once_alt()
{
	flash_leds_alt(1, 50);
	return {};
}

TaskExecutionResult KernelTestsClass::red_on()
{
	digitalWrite(RED_LED_PIN, HIGH);
	return {};
}

TaskExecutionResult KernelTestsClass::red_off()
{
	digitalWrite(RED_LED_PIN, LOW);
	return {};
}

TaskExecutionResult KernelTestsClass::gr_on()
{
	digitalWrite(GREEN_LED_PIN, HIGH);
	return {};
}

TaskExecutionResult KernelTestsClass::gr_off()
{
	digitalWrite(GREEN_LED_PIN, LOW);
	return {};
}

TaskExecutionResult KernelTestsClass::blue_on()
{
	digitalWrite(BLUE_LED_PIN, HIGH);
	return {};
}

TaskExecutionResult KernelTestsClass::blue_off()
{
	digitalWrite(BLUE_LED_PIN, LOW);
	return {};
}

TaskExecutionResult KernelTestsClass::yellow_on()
{
	digitalWrite(YELLOW_LED_PIN, HIGH);
	return {};
}

TaskExecutionResult KernelTestsClass::yellow_off()
{
	digitalWrite(YELLOW_LED_PIN, LOW);
	return {};
}

TaskExecutionResult KernelTestsClass::delay_500()
{
	delay(500);
	return {};
}


TaskExecutionResult KernelTestsClass::kill_check()
{
	if (digitalRead(KILL_SWITCH_PIN) == LOW)
	{
		flash_leds(20, 100);

		//kill system
		Serial.println("KILLED. Now entering LONG_MAX NOP delay loop");
		delay(INT16_MAX);
		delay(INT16_MAX);
		delay(INT16_MAX);
		delay(INT16_MAX);
		exit(1);
	}
	return {};
}

TaskExecutionResult KernelTestsClass::process_pause()
{
	while (digitalRead(PAUSE_BUTTON_PIN) == LOW)
	{
		digitalWrite(GREEN_LED_PIN, HIGH);
		delay(30);
		digitalWrite(GREEN_LED_PIN, LOW);
		delay(30);
	}
	return {};
}

TaskExecutionResult KernelTestsClass::task_func_delay_random()
{
	long rand_delay = random(4);
	delay(rand_delay);
	//println_value("Simulated workload. Execution time in ms: ", rand_delay);
	return {};
}


TaskExecutionResult KernelTestsClass::inc_critical()
{
	critical_exec_count++;
	return {};
}

TaskExecutionResult KernelTestsClass::inc_medium()
{
	med_exec_count++;
	return {};
}

TaskExecutionResult KernelTestsClass::inc_low()
{
	med_exec_count++;
	return {};
}

TaskExecutionResult KernelTestsClass::print_kernel_report()
{
	//FIX

	println_value("--------KERNEL REPORT #", ++print_count);
	println_value("*counts last reported last executed in ms ago: ", millis() - last_printed);
	last_printed = millis();
	println_value("Kernel Utilization %", Kernel.get_kernel_utilization());
	println_value("Kernel Executing Loop #", Kernel.get_loop_count());
	println("--------END KERNEL REPORT");
	return {};
}

TaskExecutionResult KernelTestsClass::print_loop_count()
{
	println_value("Average Loops per Second", static_cast<long>(Kernel.loop_counter.get_average_loops_per_second()));
	return {};
}


TaskExecutionResult KernelTestsClass::task_func_interval_5000()
{
	println_value("5 second interval task - last executed in ms ago: ", millis() - last_execute);
	last_execute = millis();
	return {};
}

TaskExecutionResult KernelTestsClass::exec_serial_diagnostics()
{
#ifndef ARDUINO_SIM
	SerialDiagnostics.process();
#endif

	return {};
}

KernelTask task_red_on = KernelTask(KernelTestsClass::red_on);

void KernelTestsClass::setup_blink_test_with_delays_tasks()
{
	Kernel.set_exec_limits(10, 0);
	Kernel.add_task(KERNEL_P_CRITICAL, &task_red_on);
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::delay_500));
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::red_off));
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::delay_500));
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::inc_critical));
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::print_kernel_report, false, 5000));
}

KernelTask task_flash_leds_with_resume = KernelTask(flash_leds_r, flash_leds_r_resume, false, 500);

void KernelTestsClass::setup_blink_test_with_resume_tasks()
{
	Kernel.set_exec_limits(10, 1);

	Kernel.add_task(KERNEL_P_MEDIUM, &task_flash_leds_with_resume);
}


void KernelTestsClass::setup_loop_countering_test_tasks()
{
	Kernel.set_exec_limits(100, 2);
	Kernel.add_task(KERNEL_P_CRITICAL, &task_red_on);
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::print_kernel_report, false, 5000));
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::inc_critical));
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::task_func_interval_5000, false, 5000));
	for (int i = 0; i < 3; i++)
	{
		Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::task_func_delay_random));
		Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::task_func_delay_random, false, random(i * 1000)));
	}
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::red_off));

	Kernel.add_task(KERNEL_P_MEDIUM, new KernelTask(KernelTestsClass::yellow_on));
	Kernel.add_task(KERNEL_P_MEDIUM, new KernelTask(KernelTestsClass::inc_medium));
	for (int i = 0; i < 20; i++)
	{
		Kernel.add_task(KERNEL_P_MEDIUM, new KernelTask(KernelTestsClass::task_func_delay_random));
	}
	Kernel.add_task(KERNEL_P_MEDIUM, new KernelTask(KernelTestsClass::yellow_off));

	Kernel.add_task(KERNEL_P_LOW, new KernelTask(KernelTestsClass::blue_on));
	Kernel.add_task(KERNEL_P_LOW, new KernelTask(KernelTestsClass::inc_low));
	for (int i = 0; i < 20; i++)
	{
		Kernel.add_task(KERNEL_P_LOW, new KernelTask(KernelTestsClass::task_func_delay_random));
	}
	Kernel.add_task(KERNEL_P_LOW, new KernelTask(KernelTestsClass::blue_off));
}

bool preempt_test_inc = true;
int delay_inc_current = 1;

TaskExecutionResult KernelTestsClass::delay_incrementing()
{
	delay(delay_inc_current);
	if (preempt_test_inc)
		delay_inc_current++;
	else if (delay_inc_current > 1)
		delay_inc_current--;
	return {};
}

int med_exec_count_preempt_test = 0;

TaskExecutionResult KernelTestsClass::delay_1_medium()
{
	delay(1);
	med_exec_count_preempt_test++;
	return {};
}

int low_exec_count_preempt_test = 0;

TaskExecutionResult KernelTestsClass::delay_1_low()
{
	delay(1);
	low_exec_count_preempt_test++;
	return {};
}

int preempt_test_exec_limit = 300;
bool has_reached_full_preempt = false;

TaskExecutionResult KernelTestsClass::preempt_test_print_report()
{

	//if(kernel.get_kernel_utilization() < 75)
	//	return TaskExecutionResult();



	if(Kernel.get_loop_count() > 1)
	{
		println_value("**********PREEMPT TEST REPORT #", ++print_count);
		println_value("Kernel Utilization %", Kernel.get_kernel_utilization());
		println_value("Kernel Executing Loop #", Kernel.get_loop_count());
		println_value("Last Loop Time: ", Kernel.last_loop_exec_time);
		println_value("Medium tasks executed: ", med_exec_count_preempt_test);
		if (med_exec_count_preempt_test < 5)
			println("*MEDIUM TASKS PREEMPTED*");
		println_value("Low tasks executed: ", low_exec_count_preempt_test);
		if (low_exec_count_preempt_test < 5)
			println("*LOW TASKS PREEMPTED*");

		if (med_exec_count_preempt_test == 1 && low_exec_count_preempt_test == 0)
		{
			println("*REACHED TOTAL PREEMPTION - REVERSING*");
			if (!has_reached_full_preempt)
			{
				has_reached_full_preempt = true;
				println("*REVERSING*");
				delay_inc_current += 50;
				preempt_test_inc = false;
				flash_leds_alt(500, 100);
			}
		}
		println("**********END PREEMPT TEST REPORT");
	}
	med_exec_count_preempt_test = 0;
	low_exec_count_preempt_test = 0;

	return {};
}


void KernelTestsClass::setup_test_med_low_preemption()
{
	Kernel.set_exec_limits(preempt_test_exec_limit, preempt_test_exec_limit - 1);
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::preempt_test_print_report));
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::delay_incrementing));

	Kernel.add_task(KERNEL_P_MEDIUM, new KernelTask(KernelTestsClass::delay_1_medium));
	Kernel.add_task(KERNEL_P_MEDIUM, new KernelTask(KernelTestsClass::delay_1_medium));
	Kernel.add_task(KERNEL_P_MEDIUM, new KernelTask(KernelTestsClass::delay_1_medium));
	Kernel.add_task(KERNEL_P_MEDIUM, new KernelTask(KernelTestsClass::delay_1_medium));
	Kernel.add_task(KERNEL_P_MEDIUM, new KernelTask(KernelTestsClass::delay_1_medium));

	Kernel.add_task(KERNEL_P_LOW, new KernelTask(KernelTestsClass::delay_1_low));
	Kernel.add_task(KERNEL_P_LOW, new KernelTask(KernelTestsClass::delay_1_low));
	Kernel.add_task(KERNEL_P_LOW, new KernelTask(KernelTestsClass::delay_1_low));
	Kernel.add_task(KERNEL_P_LOW, new KernelTask(KernelTestsClass::delay_1_low));
	Kernel.add_task(KERNEL_P_LOW, new KernelTask(KernelTestsClass::delay_1_low));

}

TaskExecutionResult KernelTestsClass::println_int(int value)
{
	DBG_PRINTLN(value);
	return {};
}

TaskExecutionResult KernelTestsClass::println_char(const char* value)
{
	DBG_PRINTLN(value);
	return {};
}



void KernelTestsClass::setup_param_passing_test()
{
	Kernel.set_exec_limits(100, 10);

	Kernel.add_task(KERNEL_P_CRITICAL, new KernelParamTask<int, TaskIntParamFunc>(KernelTestsClass::println_int, (int)7685, false, 500));
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelParamTask<const char*, TaskCharParamFunc>(KernelTestsClass::println_char, "Hello World!", false, 1000));

}

void KernelTestsClass::setup_param_passing_test2()
{
	Kernel.set_exec_limits(100, 10);
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelParamTask<const char*, TaskCharParamFunc>(KernelTestsClass::println_char, "Goodbye World!", false, 1000));
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelParamTask<const char*, TaskCharParamFunc>(KernelTestsClass::println_char, "Hello World!", true, 100));
}


TaskExecutionResult KernelTestsClass::inc_auto_create_task(int current_counter)
{
	println_value("One time task. Value: ", current_counter);
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelParamTask<int, TaskIntParamFunc>(KernelTestsClass::inc_auto_create_task, (int)current_counter+1, true, 1000));

	return {};
}

void KernelTestsClass::setup_create_one_time_every_execution_test()
{
	Kernel.set_exec_limits(500, 0);
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelParamTask<const char*, TaskCharParamFunc>(KernelTestsClass::println_char, "Counter Starting!", true, 0));
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelParamTask<int, TaskIntParamFunc>(KernelTestsClass::inc_auto_create_task, (int)1, true, 500));
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelParamTask<int, TaskIntParamFunc>(KernelTestsClass::inc_auto_create_task, (int)1, true, 500));


}

void KernelTestsClass::setup_many_one_time_tasks()
{
}


void KernelTestsClass::setup()
{
	DBG_PRINTLN("sketch.setup() start");

	pinMode(RED_LED_PIN, OUTPUT);
	pinMode(YELLOW_LED_PIN, OUTPUT);
	pinMode(BLUE_LED_PIN, OUTPUT);
	pinMode(GREEN_LED_PIN, OUTPUT);
	pinMode(10, INPUT_PULLUP);
	pinMode(9, INPUT_PULLUP);

#ifndef ARDUINO_SIM
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::exec_serial_diagnostics, false, 1));
#endif
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::kill_check));
	Kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(KernelTestsClass::process_pause));
	Kernel.add_task(KERNEL_P_POST, new KernelTask(KernelTestsClass::print_loop_count, false, 5000));
	Kernel.add_task(KERNEL_P_POST, new KernelTask(KernelTestsClass::print_kernel_report, false, 5000));
	Kernel.set_exec_limits(100, 0);

	Kernel.add_task(KERNEL_P_MEDIUM, new SomeLoopingTask_NonBlockingMacros(false, 0), true);

	// Add tasks of different priorities to the Kernel
	//setup_loop_countering_test_tasks();
	//setup_blink_test_with_delays_tasks();
	//setup_blink_test_with_resume_tasks();
	//setup_test_med_low_preemption();
	//setup_param_passing_test();
	//setup_param_passing_test2();
	//setup_create_one_time_every_execution_test();

	DBG_PRINTLN("sketch.setup() end");
}


void KernelTestsClass::loop()
{
	DBG_PRINTLN("sketch.loop() start");
	Kernel.run();
	DBG_PRINTLN("sketch.loop() end");


	//if (digitalRead(PAUSE_BUTTON_PIN) == LOW)
	//{
	//	start_serial();
	//	delay(1000);
	//	while (true)
	//	{
	//		Serial.println("Test paused via button");
	//		delay(2000);
	//		if (digitalRead(PAUSE_BUTTON_PIN) == LOW)
	//		{
	//			Serial.println("Test resumed via button");
	//			stop_serial();
	//			delay(1000);
	//			break;
	//		}
	//	}
	//}
}
