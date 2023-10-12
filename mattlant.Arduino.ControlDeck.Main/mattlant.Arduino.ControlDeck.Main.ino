#ifndef ARDUINO_SIM
#ifndef ESP32
#include <HID.h>
#endif

#include <LiquidCrystal.h>
#include <PCF8574.h>
#include "tests/SerialTermTest.h"
#endif


#include <Keyboard.h>
#include <Joystick.h>

#include "mattlant.Arduino.ControlDeckOS.Lib.NoArch.h"
#include "tests/KernelControlFirstTest.h"


#include "tests/KernelTests.h"
KernelTestsClass test = KernelTestsClass();

void setup()
{
	ml::setup();
	//test.setup();
#ifndef ARDUINO_SIM
	//SerialTermTestClass::setup();
	#endif

}


void loop()
{
	ml::loop();
	//test.loop();

	//kernel.run();
#ifndef ARDUINO_SIM
	//SerialTermTestClass::loop();
	#endif



	//#ifdef USE_LOOP_COUNTER
	//	lc_process();
	//#endif
}
