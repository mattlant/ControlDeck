// PCF8574OuputChannel.h

#ifndef _PCF8574OUPUTCHANNEL_h
#define _PCF8574OUPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <PCF8574.h>

#include "OutputDevice.h"

class PCF8574OuputDevice : public OutputDevice
{
 protected:
	PCF8574* io_board_;
	byte io_address_;
	byte* input_modes_;


 public:
	PCF8574OuputDevice(uint8_t io_address, byte output_ids[], byte output_count);
	void begin_() override;
	void write(byte output_pin, int value) override;
	void write_digital_multi(int value) override;

};	



#endif

