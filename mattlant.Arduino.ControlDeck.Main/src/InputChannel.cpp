#include "InputChannel.h"

InputChannel::~InputChannel() = default;

InputChannel::InputChannel(int input_ids[], int input_count): input_ids_(input_ids), input_count_(input_count)
{
}

inline int InputChannel::read(int input_id)
{
	return 0;
}

void InputChannel::begin()
{
}

