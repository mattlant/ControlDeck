// 
// 
// 

#include "lcd_test.h"
#include <LiquidCrystal.h>
#include "../src/ControlProcessor.h"
#include "../src/Devices/MainBoardInputDevice.h"
#include "../src/Devices/MainBoardOutputDevice.h"
#include "../src/Devices/MatrixInputDevice.h"
#include "../src/Devices/NullOutputDevice.h"
#include "../src/Devices/PCF8574InputDevice.h"
#include "../src/Devices/PCF8574OuputDevice.h"
#include "../src/Controls/MomentaryButton.h"
#include "../src/SerialDiagnostics.h"
#include "src/Controls/AnalogJoystickControl.h"
#include "src/Devices/LcdOutputDevice.h"

namespace lcd_test
{
	const int rs = 6, en = 10, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

	constexpr uint8_t LOOP_DELAY = 1;
	constexpr uint8_t LOOP_DELAY_MICROS = 1;


	NullOutputDevice* null_output_channel = new NullOutputDevice();

	LcdOutputDevice* lcd_output_device = new LcdOutputDevice(rs, en, d4, d5, d6, d7, 10);

	ControlProcessor* processor = new ControlProcessor(LOOP_DELAY);

	//byte row_pins[2] = {14, 15};
	//MainBoardOutputChannel* rows_channel = new MainBoardOutputChannel(row_pins, 2);
	byte in_pins[3] = {9, A0, A1};
	byte in_modes[3] = {INPUT_PULLUP,INPUT, INPUT};
	MainBoardInputDevice* mainboard_inputs = new MainBoardInputDevice(in_pins, 3, in_modes);
}

void lcd_test::setup()
{
	Serial.begin(115200);

	processor
		->add_passive_device(lcd_output_device);
	processor
		->add_active_device(mainboard_inputs);

	processor
		->add_control(new MomentaryButton(mainboard_inputs, 0, lcd_output_device, 0))
		->add_control(new AnalogJoystickControl(mainboard_inputs, lcd_output_device, 1, 2, 1, 2));

	processor->begin();
}


namespace lib_test
{
}

void lcd_test::loop()
{
	//SerialDiagnostics.process();

	processor->process();
}
