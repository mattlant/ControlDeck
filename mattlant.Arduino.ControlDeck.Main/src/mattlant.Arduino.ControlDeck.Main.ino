#include "PCF8574InputChannel.h"
#include "MainBoardInputChannel.h"
#include "JoystickOutputChannel.h"

#include "ButtonBase.h"
#include "MomentaryButton.h"
#include "ToggleSwitch.h"

#include "ButtonBox.h"


constexpr uint8_t LOOP_DELAY = 20;
constexpr uint8_t BUTTON_COUNT = 2;

//Setup input channels
int uno_pins[2] = {4,7};
MainBoardInputChannel uno_input_channel = MainBoardInputChannel(uno_pins, 2);
int ioboard1_pins[2] = {4,7};
PCF8574 io_board_1 = PCF8574(0x20); //TODO: Have created by channel
PCF8574InputChannel ioboard1_input_channel = PCF8574InputChannel(&io_board_1, ioboard1_pins, 2);

//Setup output channel (joystick only for now)
int joystick_button_ids[2] = {0,1};
JoystickOutputChannel joystick_channel = JoystickOutputChannel(0x01, joystick_button_ids, 2);

//Create controls and a basic button box
MomentaryButton btn1 = MomentaryButton(&uno_input_channel,4, &joystick_channel, 0);
ToggleSwitch ts1 = ToggleSwitch(&uno_input_channel,7, &joystick_channel, 1, 9);
ButtonBase* buttons_array[BUTTON_COUNT] = {&ts1, &btn1};
ButtonBox button_box = ButtonBox(buttons_array, BUTTON_COUNT, LOOP_DELAY);

void setup()
{
	joystick_channel.setup();
	button_box.setup();
	uno_input_channel.setup();
	ioboard1_input_channel.setup();
}

void loop()
{
	button_box.process();
}
