// 
// 
// 

#ifndef ARDUINO_SIM
#include <PCF8574.h>
#else
#endif

#include "PCF8574InputDevice.h"
#include "../util.h"


PCF8574InputDevice::PCF8574InputDevice(uint8_t io_address, byte input_ids[], byte input_count, byte input_modes[]):
	InputDevice(input_ids, input_count),
	input_modes_(input_modes)

{
	io_board_ = new PCF8574(io_address);

	if(input_ids == nullptr)
	{
		channel_map_ = new byte[8];
		for (byte i = 0; i < 8; i++)
		{
			channel_map_[i] = i;
		}
	}

	if(input_modes == nullptr)
	{
		input_modes_ = new byte[8];
	}

}

PCF8574InputDevice::PCF8574InputDevice(uint8_t io_address):
	PCF8574InputDevice(io_address, nullptr, 8, nullptr)

{

}

int PCF8574InputDevice::read_digital_multi()
{
	int result = 0;
	PCF8574::DigitalInput pfc_result = io_board_->digitalReadAll();

	if(pfc_result.p0)
		bitSet(result, 0);
	if(pfc_result.p1)
		bitSet(result, 1);
	if(pfc_result.p2)
		bitSet(result, 2);
	if(pfc_result.p3)
		bitSet(result, 3);
	if(pfc_result.p4)
		bitSet(result, 4);
	if(pfc_result.p5)
		bitSet(result, 5);
	if(pfc_result.p6)
		bitSet(result, 6);
	if(pfc_result.p7)
		bitSet(result, 7);

	return result;
}

int PCF8574InputDevice::read(byte pin_id)
{
	uint8_t value = io_board_->digitalRead(pin_id);

#if IO_DEBUG
	DBG_PRINT("pcf.read, pin=");
	DBG_PRINT(pin_id);
	DBG_PRINT(" value=");
	DBG_PRINTLN(value);
	delay(200);
#endif // IO_DEBUG

	return value;
}


void PCF8574InputDevice::begin_()
{
	DBG_PRINTLN("pcf.begin");

	io_board_->setLatency(10);

	for (int i = 0; i < channel_count_; i++)
	{
		DBG_PRINT("---setting pin to input: ");
		DBG_PRINTLN(channel_map_[i]);
		io_board_->pinMode(channel_map_[i], input_modes_ == nullptr ? INPUT_PULLUP : input_modes_[i]);
	}

	//for (int i = 0; i < 8; i++)
	//	io_board_->pinMode(i, INPUT_PULLUP);
	io_board_->begin();
}

PCF8574CachingInputDevice::PCF8574CachingInputDevice(uint8_t io_address, byte input_ids[], byte input_count,
	byte input_modes[]): PCF8574InputDevice(io_address, input_ids, input_count, input_modes)
{
}

PCF8574CachingInputDevice::PCF8574CachingInputDevice(uint8_t io_address): PCF8574InputDevice(io_address)
{
}


void PCF8574CachingInputDevice::process_()
{
	input_value_ = read_digital_multi();
}

int PCF8574CachingInputDevice::read(byte pin_id)
{
	return bitRead(input_value_, pin_id);
}

