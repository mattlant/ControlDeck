#ifndef ARDUINO_SIM
#include "../src/SerialDiagnostics.h"
#endif

#include "../src/util.h"
#include "KernelControlFirstTest.h"
#include "../src/Devices/MainBoardInputDevice.h"
#include "../src/Controls/MomentaryButton.h"
#include "../src/Devices/MainBoardOutputDevice.h"
#include "../src/OS/CDKernel.h"


namespace KernelControlFirstTest
{

	TaskExecutionResult print_loop_count()
	{
		DBG_PRINT("Average Loops per Second: ");
		DBG_PRINTLN(static_cast<int>(Kernel.loop_counter.get_average_loops_per_second()));
		return TaskExecutionResult();
	}



	MainBoardInputDevice mainboard_input_channel = MainBoardInputDevice{10};

	MainBoardOutputDevice led_out = MainBoardOutputDevice{7};


	MomentaryButton* btn1 = new MomentaryButton(&mainboard_input_channel, 0, &led_out, 0, 5);

	void setup()
	{
		Serial.begin(115200);
		mainboard_input_channel.set_input_modes(0, INPUT_PULLUP);
		mainboard_input_channel.begin();
		led_out.begin();

		btn1->set_negate_state_(true);
		btn1->setup();
		btn1->interval = 0;

		Kernel.add_task(KERNEL_P_POST, new KernelTask(print_loop_count, false, 1000));
		Kernel.add_task(KERNEL_P_MEDIUM, btn1);
		Kernel.setup();
	}

	void loop()
	{
		Kernel.run();
	}
}
