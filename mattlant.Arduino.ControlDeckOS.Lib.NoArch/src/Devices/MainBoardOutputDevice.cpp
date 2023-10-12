// 
// 
// 

#include "MainBoardOutputDevice.h"
#include "../util.h"

void MainBoardOutputDevice::begin_()
{
	DBG_PRINTLN("mainboardout.begin");

	for (int i = 0; i < channel_count_; i++)
	{
		DBG_PRINT("Channel:");
		DBG_PRINT(i);
		DBG_PRINT(" - setting pin to output: ");
		DBG_PRINTLN(channel_map_[i]);
		pinMode(channel_map_[i], OUTPUT);
		delay(200);
	}
}

void MainBoardOutputDevice::write(byte output_pin, int value)
{
	digitalWrite(channel_map_[output_pin], value);
}
