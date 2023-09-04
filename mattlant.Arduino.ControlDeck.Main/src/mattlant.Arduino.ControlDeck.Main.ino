#include "InputChannelFactory.h"
#include <Joystick.h>
#include <PCF8574.h>
#include "ButtonBox.h"
#include "ButtonBase.h"
#include "MainBoardInputChannel.h"
#include "MomentaryButton.h"
#include "PCF8574InputChannel.h"
#include "ToggleSwitch.h"

constexpr uint8_t LOOP_DELAY = 20;
constexpr uint8_t BUTTON_COUNT = 2;

int uno_pins[2] = {4,7};
int ioboard1_pins[2] = {4,7};

MainBoardInputChannel uno_input_channel = MainBoardInputChannel(uno_pins, 2);
PCF8574 io_board_1 = PCF8574(0x20);
PCF8574InputChannel ioboard1_input_channel = PCF8574InputChannel(&io_board_1, ioboard1_pins, 2);


MomentaryButton btn1 = MomentaryButton(&uno_input_channel,4, 2);
ToggleSwitch ts1 = ToggleSwitch(&uno_input_channel,7, 0, 9);
ButtonBase* buttons_array[BUTTON_COUNT] = {&ts1, &btn1};
ButtonBox button_box = ButtonBox(buttons_array, BUTTON_COUNT, LOOP_DELAY);

void setup()
{
	uno_input_channel.setup();
	ioboard1_input_channel.setup();
	button_box.setup();
}

void loop()
{
	button_box.process();
}
