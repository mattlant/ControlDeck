// 
// 
// 

#include "KeyboardOutputDevice.h"

KeyboardOutputDevice::KeyboardOutputDevice(): OutputDevice()
{
}

void KeyboardOutputDevice::begin_()
{
	Keyboard.begin();
}

void KeyboardOutputDevice::write(byte output_id, int value)
{
	if (value == 0)
		return;
	Keyboard.write(output_id);
}
