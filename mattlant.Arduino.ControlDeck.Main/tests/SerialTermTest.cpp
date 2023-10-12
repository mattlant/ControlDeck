// 
// 
// 

#include "SerialTermTest.h"


#include "../src/util.h"
#include "../src/Devices/DeviceKernelTask.h"
#include "../src/OS/CDKernel.h"
#include "..\src\Serial\MShell.h"
#ifndef ARDUINO_SIM
#include "..\src\Serial\ArduinoHWSerial_StandardIO.h"
#include "../src/Serial/SerialDiagnostics.h"
#endif


namespace SerialTermTestClass
{
	CDKernel kernel = CDKernel(millis, delay, 100, 0);

	MShell terminal = MShell(new HardwareSerialInput(), new HardwareSerialOutput());


	void setup()
	{
		terminal.begin();

#ifndef ARDUINO_SIM
		//kernel.add_task(KERNEL_P_CRITICAL, new KernelTask(exec_serial_diagnostics, false, 1));
#endif

		//kernel.add_task(KERNEL_P_MEDIUM, &fake_button1);
		//kernel.add_task(KERNEL_P_MEDIUM, &fake_button2);
		//kernel.add_task(KERNEL_P_POST, new KernelTask(print_loop_count, false, 5000));

		//kernel.setup();
	}

	void loop()
	{
		terminal.process();
		delay(1);
		//kernel.run();
	}
}
