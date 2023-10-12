#include "lib_test.h"

#include "../src/ControlProcessor.h"
#include "../src/Devices/MainBoardInputDevice.h"
#include "../src/Devices/MainBoardOutputDevice.h"
#include "../src/Devices/MatrixInputDevice.h"
#include "../src/Devices/NullOutputDevice.h"
#include "../src/Devices/PCF8574InputDevice.h"
#include "../src/Devices/PCF8574OuputDevice.h"
#include "../src/Controls/MomentaryButton.h"
#include "../src/SerialDiagnostics.h"

namespace lib_test
{
	constexpr uint8_t LOOP_DELAY = 0;
	constexpr uint8_t LOOP_DELAY_MICROS = 1;


	byte out_pins[5] = {10};
	MainBoardOutputDevice* led_channel = new MainBoardOutputDevice(out_pins, 1);
	NullOutputDevice* null_output_channel = new NullOutputDevice();

	ControlProcessor* processor = new ControlProcessor(LOOP_DELAY);

	//byte row_pins[2] = {14, 15};
	//MainBoardOutputChannel* rows_channel = new MainBoardOutputChannel(row_pins, 2);
	byte col_pins[2] = {8, 9};
	byte col_pin_modes[2] = {INPUT_PULLUP, INPUT_PULLUP};
	MainBoardInputDevice* cols_channel = new MainBoardInputDevice(col_pins, 2, col_pin_modes);

	byte row_pins[2] = {0, 1};
	PCF8574OuputDevice* rows_channel = new PCF8574OuputDevice(PCF_ADDR_B001, row_pins, 2);


	byte col_channels[2] = {0,1};
	//byte col_pin_modes[2] = {INPUT, INPUT};
	//PCF8574InputChannel* cols_channel = new PCF8574InputChannel(PCF_ADDR_B000, col_pins, 2, col_pin_modes);
	MatrixInputDevice* matrix_input_channel = new MatrixInputDevice(rows_channel, cols_channel, 2, 2, row_pins,
	                                                                  col_channels, LOW);

}

void lib_test::setup()
{
	Serial.begin(115200);
#ifndef ARDUINO_SIM

	processor
		->add_passive_device(led_channel);
	processor
		->add_active_device(matrix_input_channel);

	processor
		->add_control(new MomentaryButton(matrix_input_channel, 0, led_channel, 0))
		->add_control(new MomentaryButton(matrix_input_channel, 1, led_channel, 0))
		->add_control(new MomentaryButton(matrix_input_channel, 2, led_channel, 0))
		->add_control(new MomentaryButton(matrix_input_channel, 3, led_channel, 0));

	processor->begin();

#endif
}

void lib_test::loop()
{
#ifndef ARDUINO_SIM
	SerialDiagnostics.process();

	processor->process();
#endif
}
