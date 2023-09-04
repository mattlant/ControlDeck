# ControlDeck for Arduino - An easy way to build out input controls for your projects

This is the start of a large library of classes that can help you to build input/output controls efficiently and effectively for your projects in a very short amount of time. Check out the example below.

_Note: This is a work in progress and subject to much change, and may get messy at times._

A few highlights so far:
- Clean and modular framework that will keep your code clean and easy to maintain and extend.
- MomentaryButton - easy way to build out a simple push button.
- Rotary Encoders with push button support. This is early work and is a polled implementation, but works well enough. (Based on https://github.com/John-Lluch/Encoder)
Unfortunately this only works right now with MainBoardInputChannel for the encoder inputs.
- ToggleSwitch - Have a sim racing game where the 'On' for the car is a momentary button, but you want to use a 
**REAL** toggle or key ignition switch? Now you can! This will simulate the button presses the game expects to toggle on and off.
- ButtonBox - A processor for controlling a button box you can use for sim racing, flights sims and more.
- Outputs are abstracted as OutputChannel, two output channels are ready and More can be easily created, such as a midi or a serial output channel.
	- Joystick (uses Joystick Library. Requires Leonardo/Micro.) 
	- Keyboard (Requires Leonardo/Micro.) 
	- MainboardOutputChannel for outputting to digital pins on your device. (IO Expander output coming soon)
	- Null - for testing!
- Inputs are abstracted as InputChannel, with two input channels ready: 
	- Arduino mainboard pin inputs 
	- PFC8574 IO Expander support - Expand your digital inputs with built in support for this chip/board via PFC8574InputChannel.
- Each control can utilize it’s own channel mapping for full control of inputs and outputs.

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
