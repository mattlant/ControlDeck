// 
// 
// 

#include "enc_test.h"

#include "src/ControlProcessor.h"
#include "src/SerialDiagnostics.h"
#include "src/Controls/Encoder.h"
#include "src/Devices/MainBoardInputDevice.h"
#include "src/Devices/MainBoardOutputDevice.h"
#include "src/Devices/PCF8574InputDevice.h"

namespace enc_test
{
	constexpr uint8_t LOOP_DELAY = 0;
	constexpr uint8_t LOOP_DELAY_MICROS = 1;

	ControlProcessor* processor = new ControlProcessor(LOOP_DELAY);

	byte led_pins[5] = {8};
	byte mb_in_pins[3] = {14, 15, 16};
	byte pcf_in_pins[4] = {0, 1, 2, 3};
	MainBoardOutputDevice* led_channel = new MainBoardOutputDevice(led_pins, 1);
	MainBoardInputDevice* mainboard_input_channel = new MainBoardInputDevice(mb_in_pins, 3, nullptr);
	PCF8574CachingInputDevice* ioboard1_input_channel = new PCF8574CachingInputDevice(
		PCF_ADDR_B000, pcf_in_pins, 4, nullptr);
}


void enc_test::setup()
{
	Serial.begin(115200);
#ifndef ARDUINO_SIM


	processor
		->add_passive_device(mainboard_input_channel)
		->add_passive_device(led_channel);
	processor
		->add_active_device(ioboard1_input_channel);

	processor
		->add_control(new Encoder(mainboard_input_channel, 0, 1, 2, led_channel, 0, 0, 0))
		->add_control(new Encoder(ioboard1_input_channel, 1, 2, 3, led_channel, 0, 0, 0));

	processor->begin();

#endif
}

void enc_test::loop()
{
#ifndef ARDUINO_SIM
	SerialDiagnostics.process();

	processor->process();
#endif
}
