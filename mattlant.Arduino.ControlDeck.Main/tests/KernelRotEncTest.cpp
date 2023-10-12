#ifndef ARDUINO_SIM
#include "../src/SerialDiagnostics.h"
#endif

#include "../src/util.h"
#include "../src/Devices/DeviceKernelTask.h"
#include "../src/Devices/MainBoardInputDevice.h"
#include "../src/Devices/PCF8574InputDevice.h"
#include "../src/Controls/MomentaryButton.h"
#include "../src/Controls/Encoder.h"
#include "../src/Devices/MainBoardOutputDevice.h"
#include "../src/OS/Kernel.h"


#include "KernelRotEncTest.h"

#include "src/Controls/LatchToMomentary.h"
#include "src/Devices/MuxInputDevice.h"
#include "src/Serial/SerialDiagnostics.h"


namespace KernelRotEncTest
{
	template <typename... Args>
	int* createAndFillArray(Args... args)
	{
		// Create an array of the required size.
		int* arr = new int[sizeof...(args)];

		// Use fold expressions to fill the array.
		int index = 0;
		((arr[index++] = args), ...);

		return arr;
	}


	TaskExecutionResult print_loop_count()
	{
		DBG_PRINT("Average Loops per Second: ");
		DBG_PRINTLN(kernel.loop_counter.get_average_loops_per_second());
		return {};
	}


	MainBoardInputDevice mux_signal_in = MainBoardInputDevice(8);
	PCF8574CachingInputDevice pcf8574_1 = PCF8574CachingInputDevice(PCF_ADDR_B000);
	PCF8574CachingInputDevice pcf8574_2 = PCF8574CachingInputDevice(PCF_ADDR_B001);

	MainBoardOutputDevice led_out = MainBoardOutputDevice(9, 7);
	MainBoardOutputDevice mux_out = MainBoardOutputDevice(10, 14, 15, 16);

	MuxInputDevice mux = MuxInputDevice(&mux_signal_in, 0, &mux_out, 0, 1, 2, 3);

	Encoder enc_1 = Encoder(&pcf8574_1, 0, 1, &led_out, 0, 1, 1);
	Encoder enc_2 = Encoder(&pcf8574_2, 0, 1, &led_out, 0, 1, 1);
	MomentaryButton enc_button_1 = MomentaryButton(&pcf8574_1, 2, &led_out, 0, 5);
	MomentaryButton enc_button_2 = MomentaryButton(&pcf8574_2, 2, &led_out, 1, 5);
	MomentaryButton fake_button1 = MomentaryButton(&mux, 5, &led_out, 0, 5);
	MomentaryButton fake_button2 = MomentaryButton(&mux, 15, &led_out, 0, 5);
	LatchToMomentary switch_1 = LatchToMomentary(&pcf8574_1, 3, &led_out, 0, 50);

	TaskExecutionResult exec_serial_diagnostics()
	{
#ifndef ARDUINO_SIM
		SerialDiagnostics.process();
#endif

		return TaskExecutionResult();
	}


	void setup()
	{
		Serial.begin(115200);
		mux_signal_in.set_input_modes(0, INPUT_PULLUP);
		mux_signal_in.begin();
		mux_out.begin();
		led_out.begin();
		pcf8574_1
			.set_mode(2, INPUT_PULLUP)
			->set_mode(3, INPUT_PULLUP)
			->set_mode(0, INPUT)
			->set_mode(1, INPUT);
		pcf8574_2
			.set_mode(2, INPUT_PULLUP)
			->set_mode(0, INPUT)
			->set_mode(1, INPUT);
		pcf8574_1.begin();
		pcf8574_2.begin();
		enc_button_1.set_negate_state_(true);
		enc_button_2.set_negate_state_(true);
		fake_button1.set_negate_state_(true);
		fake_button2.set_negate_state_(true);
		mux.begin();

#ifndef ARDUINO_SIM
		kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(exec_serial_diagnostics, false, 1));
#endif

		kernel.add_task(KERNEL_P_MEDIUM, new IoDeviceKernelTask(1, &pcf8574_1), true);
		kernel.add_task(KERNEL_P_MEDIUM, new IoDeviceKernelTask(1, &pcf8574_2), true);
		kernel.add_task(KERNEL_P_MEDIUM, new IoDeviceKernelTask(5, &led_out), true);
		kernel.add_task(KERNEL_P_MEDIUM, new IoDeviceKernelTask(5, &mux), true);
		kernel.add_task(KERNEL_P_MEDIUM, &enc_1);
		kernel.add_task(KERNEL_P_MEDIUM, &enc_button_1);
		kernel.add_task(KERNEL_P_MEDIUM, &enc_2);
		kernel.add_task(KERNEL_P_MEDIUM, &enc_button_2);
		kernel.add_task(KERNEL_P_MEDIUM, &switch_1);
		//kernel.add_task(KERNEL_P_MEDIUM, &fake_button1);
		//kernel.add_task(KERNEL_P_MEDIUM, &fake_button2);
		kernel.add_task(KERNEL_P_POST, new KernelTask(print_loop_count, false, 5000));

		kernel.setup();
	}

	void loop()
	{
		kernel.run();
	}
}
