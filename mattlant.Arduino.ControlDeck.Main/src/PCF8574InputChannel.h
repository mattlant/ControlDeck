// PCF8574InputChannel.h
#ifndef PFC8574INPUTCHANNEL_h
#define PFC8574INPUTCHANNEL_h



#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "InputChannel.h"

#include <PCF8574.h>

constexpr uint8_t PCF_ADDR_B000 = 0x20;
constexpr uint8_t PCF_ADDR_B001 = 0x21;
constexpr uint8_t PCF_ADDR_B010 = 0x22;
constexpr uint8_t PCF_ADDR_B011 = 0x23;
constexpr uint8_t PCF_ADDR_B100 = 0x24;
constexpr uint8_t PCF_ADDR_B101 = 0x25;
constexpr uint8_t PCF_ADDR_B110 = 0x26;
constexpr uint8_t PCF_ADDR_B111 = 0x27;

class PCF8574InputChannel : public InputChannel
{
public:
	PCF8574InputChannel(uint8_t io_address, int input_ids[], int input_count);


public:
	int read(int pin_id) override;
	void begin() override;

protected:
	PCF8574* io_board_;
	int io_address_;
};

#endif
