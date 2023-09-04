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

MainBoardInputChannel channel_pin_4 = MainBoardInputChannel(4);
MainBoardInputChannel channel_pin_7 = MainBoardInputChannel(7);
PCF8574 io_board_1 = PCF8574(0x20);
PCF8574InputChannel io_exp_p0 = PCF8574InputChannel(P0, &io_board_1);
PCF8574InputChannel io_exp_p1 = PCF8574InputChannel(P1, &io_board_1);


MomentaryButton btn1 = MomentaryButton(&io_exp_p0, 2);
ToggleSwitch ts1 = ToggleSwitch(&io_exp_p1, 0, 9);
ButtonBase* buttons_array[BUTTON_COUNT] = {&ts1, &btn1};
ButtonBox button_box = ButtonBox(buttons_array, BUTTON_COUNT, LOOP_DELAY);

void setup()
{
	io_exp_p0.setup();
	io_exp_p1.setup();

	button_box.setup();
	io_board_1.begin();

}
void loop()
{
	button_box.process();
}
