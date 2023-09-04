# ControlDeck for Arduino - An easy way to build out input controls for your projects

By mattlant

This is the start of a large library of classes that can help you to build input/output controls efficiently and effectively for your projects in a very short amount of time.

To build out a simple button box you would have a line count equal to the number of buttons you want + ~10. Easy! Check out the example below.

Currently not structured for library sharing but will work on that later.

A few highlights so far:
- PC connectivity is currently through Joystick HID device (Leonardo/Micro). Plans to expand connectivity in the future, 
such as keyboard, midi, serial and more via abstracted interfaces.
- ButtonBox - A simple processor for controlling a button box you can use for sim racing, flights sims and more.
- MomentaryButton - easy way to build out a simple push button.
- ToggleSwitch - Have a sim racing game where the 'On' for the car is a momentary button, but you want to use a 
REAL ignition switch? Now you can. This will simulate the button press the game expects when you switch on and off.
- PFC8574 IO Expander support - Expand your inputs with built in support for this chip/board.
- Partially implemented abstraction of inputs (e.g. pins) so you can utilize mainboard inputs, IO board inputs, 
or custom inputs, easily, just by changing which class you choose or implement a custom IOChannel.

Check back later for more updates.

Questions, comments, feedback? Feel free to reach out :)

PS - I uploaded this project 1 day after starting Arduino development(!) - I may not be following best practices for Arduino. 
If you notice anything, please let me know!

```C:
#include <PCF8574.h>
#include <Joystick.h>
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
```