#include "OutputChannel.h"

OutputChannel::OutputChannel(int output_ids[], int output_count): output_ids_(output_ids), output_count_(output_count)
{
}

OutputChannel::~OutputChannel() = default;

void OutputChannel::begin()
{
}

void OutputChannel::write(int output_id, int value)
{
}
