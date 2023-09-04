// 
// 
// 

#include "MainBoardInputChannel.h"

MainBoardInputChannel::MainBoardInputChannel(int input_ids[], int input_count): DigitalInputChannel(input_ids, input_count)
{
}

int MainBoardInputChannel::read_int(int pin_id)
{
	return digitalRead(pin_id);
}

void MainBoardInputChannel::setup()
{
	for (int i = 0; i < input_count_; i++)
		pinMode(input_ids_[i], INPUT);
}
