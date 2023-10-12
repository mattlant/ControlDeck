// 
// 
// 

#include "LcdOutputDevice.h"
#include "../util.h"

LcdOutputDevice::LcdOutputDevice(int rs, int en, int d4, int d5, int d6, int d7, int channel_count)
	: OutputDevice(), lcd_(rs, en, d4, d5, d6, d7), num_positions_(channel_count)
{
	channel_count_ = channel_count;
	for (int i = 0; i < 32; ++i)
	{
		last_values_[i] = -1; // Initialize to invalid value
	}
}

void LcdOutputDevice::begin_()
{
	DBG_PRINTLN("Lcd Channel Monitor Starting");

	lcd_.begin(16, 2);
	initialize_lcd();
}

void LcdOutputDevice::write(byte channel, int value)
{
	if (channel < 0 || channel >= num_positions_)
	{
		return; // Invalid position
	}

	if (last_values_[channel] != value)
	{
		last_values_[channel] = value;
		map_to_lcd(channel, value);
	}
}

void LcdOutputDevice::map_to_lcd(int position, int value)
{
	const int row = position / 16;
	const int col = position % 16;

	lcd_.setCursor(col, row);

	if (value == 0 || value == 1)
	{
		lcd_.print(value);
	}
	else
	{
		const int mapped_value = map(value, 0, 1024, 0, 9);
		lcd_.print(mapped_value);
	}
}

void LcdOutputDevice::initialize_lcd()
{
	for (int i = 0; i < 32; ++i)
	{
		map_to_lcd(i, i < num_positions_ ? '-' : 'X');
	}
}
