// 
// 
// 

#include "MainBoardInputDevice.h"
#include "../util.h"


void MainBoardInputDevice::set_input_modes(byte channel, byte mode)
{
	pinMode(channel_map_[channel], mode);
}

int MainBoardInputDevice::read(byte pin_id)
{

	int value = is_analog_ ?
		analogRead(channel_map_[pin_id]) :
		digitalRead(channel_map_[pin_id]);

#if IO_DEBUG
	DBG_PRINT("mianboardin.read, pin=");
	DBG_PRINT(pin_id);
	DBG_PRINT("value=");
	DBG_PRINTLN(value);
	delay(50);

#endif // IO_DEBUG

	return value;
}

void MainBoardInputDevice::begin_()
{
	DBG_PRINTLN("mainboardin.begin");

	for (int i = 0; i < channel_count_; i++)
	{
		DBG_PRINT("---setting pin to input: ");
		DBG_PRINTLN(channel_map_[i]);
		pinMode(channel_map_[i], input_modes_ == nullptr ? INPUT_PULLUP : input_modes_[i]);
	}
}
