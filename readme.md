# ControlDeck for Arduino - An easy way to build out input controls for your projects

By mattlant

This is the start of a large library of classes that can help you to build input/output controls efficiently and effectively for your projects in a very short amount of time. Check out the example below.

Currently not structured for library sharing but will work on that later.

A few highlights so far:
- Clean and modular framework that will keep your code clean and easy to maintain and extend.
- ButtonBox - A processor for controlling a button box you can use for sim racing, flights sims and more.
- MomentaryButton - easy way to build out a simple push button.
- ToggleSwitch - Have a sim racing game where the 'On' for the car is a momentary button, but you want to use a 
*REAL* ignition switch? Now you can. This will simulate the button press the game expects when you switch on and off.
- Outputs are abstracted as OutputChannel, and one output channel is ready: Joystick (Requires Leonardo/Micro.) More can be easily created, such as a keyboard, midi, or serial output channel.
- Inputs are abstracted as InputChannel, with two input channels ready: Arduino mainboard pin inputs and an IO Expander board (see below).
- Each control can utilize it’s own channel mapping for full control of input and output.
- PFC8574 IO Expander support - Expand your digital inputs with built in support for this chip/board via PFC8574InputChannel.

Check back later for more updates.

Questions, comments, feedback? Feel free to reach out :)

PS - I uploaded this project 1 day after starting Arduino development(!) - I may not be following best practices for Arduino. 
If you notice anything, please let me know!

```C
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
PCF8574InputChannel ioboard1_input_channel = PCF8574InputChannel(0x20, ioboard1_pins, 2);
//Setup output channel (joystick only for now)
int joystick_button_ids[2] = {0,1};
JoystickOutputChannel joystick_channel = JoystickOutputChannel(0x01, joystick_button_ids, 2);

//Create controls and a basic button box - Will abstract this more in the future.
MomentaryButton btn1 = MomentaryButton(&uno_input_channel,4, &joystick_channel, 0);
ToggleSwitch ts1 = ToggleSwitch(&uno_input_channel,7, &joystick_channel, 1, 9);
ButtonBase* buttons_array[BUTTON_COUNT] = {&ts1, &btn1};
ButtonBox button_box = ButtonBox(buttons_array, BUTTON_COUNT, LOOP_DELAY);

void setup()
{
	joystick_channel.begin();
	uno_input_channel.begin();
	ioboard1_input_channel.begin();
	button_box.setup();
}

void loop()
{
	button_box.process();
}

```
