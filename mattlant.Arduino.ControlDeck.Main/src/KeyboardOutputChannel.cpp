// 
// 
// 

#include <Keyboard.h>
#include "KeyboardOutputChannel.h"

void KeyboardOutputChannel::begin()
{
	Keyboard.begin();
}

void KeyboardOutputChannel::write(int output_id, int value)
{
	if(value == 0)
		return;
	Keyboard.write(output_id);
}
