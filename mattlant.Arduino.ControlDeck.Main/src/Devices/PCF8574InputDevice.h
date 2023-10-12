// PCF8574InputChannel.h
#ifndef PFC8574INPUTCHANNEL_h
#define PFC8574INPUTCHANNEL_h



#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "InputDevice.h"

#include <PCF8574.h>

#define PCF_ADDR_B000 0x20
#define PCF_ADDR_B001 0x21
#define PCF_ADDR_B010 0x22
#define PCF_ADDR_B011 0x23
#define PCF_ADDR_B100 0x24
#define PCF_ADDR_B101 0x25
#define PCF_ADDR_B110 0x26
#define PCF_ADDR_B111 0x27

class PCF8574InputDevice : public InputDevice
{
protected:
	PCF8574* io_board_;
	byte* input_modes_;

	void begin_() override;

public:

	PCF8574InputDevice(uint8_t io_address, byte input_ids[], byte input_count, byte input_modes[]);
	PCF8574InputDevice(uint8_t io_address);
	int read_digital_multi() override;

	PCF8574InputDevice* set_mode(byte channel, byte mode)
	{
		input_modes_[channel] = mode;
		return this;
	}

public:
	//todo: add caching
	int read(byte pin_id) override;


};

class PCF8574CachingInputDevice : public PCF8574InputDevice
{
public:
	PCF8574CachingInputDevice(uint8_t io_address, byte input_ids[], byte input_count, byte input_modes[]);

	PCF8574CachingInputDevice(uint8_t io_address);

protected:
	void process_() override;

public:
	int read(byte pin_id) override;
		int input_value_ = 0;

};

#endif
