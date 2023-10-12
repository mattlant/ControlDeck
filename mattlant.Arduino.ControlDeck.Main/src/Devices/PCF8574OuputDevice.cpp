// 
// 
// 

#include "PCF8574OuputDevice.h"
#include "../util.h"

PCF8574OuputDevice::PCF8574OuputDevice(uint8_t io_address, byte output_ids[], byte output_count):
	OutputDevice(output_ids, output_count)
{
	io_board_ = new PCF8574(io_address);
}

void PCF8574OuputDevice::begin_()
{
	DBG_PRINTLN("pcf.begin");

	io_board_->setLatency(10);

	for (int i = 0; i < channel_count_; i++)
	{
		DBG_PRINT("---setting pin to input: ");
		DBG_PRINTLN(channel_map_[i]);
		io_board_->pinMode(channel_map_[i], OUTPUT, LOW);
	}

	//for (int i = 0; i < 8; i++)
	//	io_board_->pinMode(i, INPUT_PULLUP);
	io_board_->begin();
}

void PCF8574OuputDevice::write(byte output_pin, int value)
{
	io_board_->digitalWrite(output_pin, value);

#if IO_DEBUG
	DBG_PRINT("pcfout.write, pin=");
	DBG_PRINT(output_pin);
	DBG_PRINT(" value=");
	DBG_PRINTLN(value);
	delay(200);

#endif // IO_DEBUG

}

void PCF8574OuputDevice::write_digital_multi(int value)
{
	PCF8574::DigitalInput multi_value;
	multi_value.p0 = value & 1 << 0;
	multi_value.p1 = value & 1 << 1;
	multi_value.p2 = value & 1 << 2;
	multi_value.p3 = value & 1 << 3;
	multi_value.p4 = value & 1 << 4;
	multi_value.p5 = value & 1 << 5;
	multi_value.p6 = value & 1 << 6;
	multi_value.p7 = value & 1 << 7;

	io_board_->digitalWriteAll(multi_value);
}
