#include "DigitalInputChannel.h"
#include <Joystick.h>
#include <PCF8574.h>
#include "ButtonBox.h"
#include "ButtonBase.h"
#include "MomentaryButton.h"
#include "ToggleSwitch.h"

constexpr uint8_t LOOP_DELAY = 10;
constexpr uint8_t BUTTON_COUNT = 4;

ToggleSwitch ts1 = ToggleSwitch(7, 0, 11);
ToggleSwitch ts2 = ToggleSwitch(8, 1, 12);
MomentaryButton btn1 = MomentaryButton(9, 2);
MomentaryButton btn2 = MomentaryButton(10, 3);
ButtonBase* buttons_array[BUTTON_COUNT] = {&ts1, &ts2, &btn1, &btn2};
ButtonBox button_box = ButtonBox(buttons_array, BUTTON_COUNT, LOOP_DELAY);

void setup()
{
	button_box.setup();
}
void loop()
{
	button_box.process();
}
