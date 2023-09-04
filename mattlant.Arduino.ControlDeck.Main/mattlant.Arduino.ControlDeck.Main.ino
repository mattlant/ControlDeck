#include "NullOutputChannel.h"
#include "src/InputDebouncer.h"
#include "StaticIntList.h"
#include "src/PCF8574InputChannel.h"
#include "src/MainBoardInputChannel.h"
#include "src/JoystickOutputChannel.h"
#include "src/KeyboardOutputChannel.h"
#include "src/ButtonBase.h"
#include "src/MomentaryButton.h"
#include "src/ToggleSwitch.h"
#include "src/ButtonBox.h"
#include "src/Encoder.h"
#include "src/MainBoardOutputChannel.h"

constexpr uint8_t LOOP_DELAY = 1;


//Setup input channels
int mainboard_pins[] = {4,7,14,15,16};
MainBoardInputChannel* mainboard_input_channel = new MainBoardInputChannel(mainboard_pins, 5);
int ioboard1_pins[] = {0,1,2};
PCF8574InputChannel* ioboard1_input_channel = new PCF8574InputChannel(PCF_ADDR_B000, ioboard1_pins, 3);
//Setup output channels
int joystick_button_ids[] = {0,1,2,3,4,5,6,7};
JoystickOutputChannel* joystick_channel = new JoystickOutputChannel(0x01, joystick_button_ids, 8);
KeyboardOutputChannel* kb_channel = new KeyboardOutputChannel();
int led_pins[] = {8,9};
MainBoardOutputChannel* led_channel = new MainBoardOutputChannel(led_pins, 2);
NullOutputChannel* null_output_channel = new NullOutputChannel();

//Create controls and a basic button box - Will abstract this more in the future.
MomentaryButton btn1 = MomentaryButton(mainboard_input_channel,4, joystick_channel, 0);
ToggleSwitch ts1 = ToggleSwitch(mainboard_input_channel,7, joystick_channel, 1, 9);
Encoder enc = Encoder(mainboard_input_channel,14, 15, 16, joystick_channel, 2,3,4);
constexpr uint8_t CONTROL_COUNT = 3;
ButtonBase* buttons_array[CONTROL_COUNT] = {&ts1, &btn1, &enc};
ButtonBox button_box = ButtonBox(buttons_array, CONTROL_COUNT, LOOP_DELAY);

void setup()
{
	//only negates push button
	enc.set_negate_input(true);

	joystick_channel->begin();
	kb_channel->begin();
	led_channel->begin();
	mainboard_input_channel->begin();
	ioboard1_input_channel->begin();
	button_box.setup();
}

void loop()
{
	button_box.process();
}
