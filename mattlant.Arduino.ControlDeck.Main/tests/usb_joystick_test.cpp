// 
// 
// 

#include "usb_joystick_test.h"

#include "../src/Controls/AnalogJoystickControl.h"
#include "../src/ControlProcessor.h"
#include "../src/Devices/MainBoardInputDevice.h"
#include "../src/Devices/SerialOutputDevice.h"
#include "../src/Devices/JoystickOutputDevice.h"

namespace usb_joystick_test
{
	constexpr uint8_t LOOP_DELAY = 10;
	constexpr uint8_t LOOP_DELAY_MICROS = 1;

	ControlProcessor* processor = new ControlProcessor(LOOP_DELAY);

	byte serial_channels[2] = {0,1};
	byte mb_in_pins[2] = {A0, A1};
	JoystickOutputDevice* joystick = new JoystickOutputDevice(0x02, 2, true, true, false);

	SerialOutputDevice* serial_device = new SerialOutputDevice(serial_channels, 2);
	MainBoardInputDevice* mainboard_input_device = new MainBoardInputDevice(mb_in_pins, 2, nullptr);
}
void usb_joystick_test::setup()
{
	joystick->joystick_->begin();
		//Serial.begin(115200, 0);
		
	processor
		->add_passive_device(joystick)
		->add_passive_device(serial_device);
	//processor
	//	->add_active_device();

	processor
		->add_control(new AnalogJoystickControl(mainboard_input_device, joystick, 0, 1, XAxis, YAxis));

	processor->begin();
	joystick->joystick_->setXAxisRange(0, 1024);
	joystick->joystick_->setYAxisRange(0, 1024);

}

void usb_joystick_test::loop()
{
	// read the value from the sensor:
	processor->process();

}
