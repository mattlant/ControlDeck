// 
// 
// 

#include "MainBoardOutputChannel.h"

MainBoardOutputChannel::MainBoardOutputChannel(int output_pins[], int output_pins_count): OutputChannel(output_pins, output_pins_count)
{
}

void MainBoardOutputChannel::begin()
{
	for (int i = 0; i < output_count_; i++)
		pinMode(output_ids_[i], OUTPUT);
}

void MainBoardOutputChannel::write(int output_pin, int value)
{
	digitalWrite(output_pin, value);
}
