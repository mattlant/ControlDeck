// 
// 
// 

#include "SerialOutputDevice.h"


void SerialOutputDevice::write(byte channel, int value)
{
	Serial.print("*c[");
	Serial.print(channel);
	Serial.print(",");
	Serial.print(value);
	Serial.println("]c*");
}

SerialOutputDevice::SerialOutputDevice(byte channel_count): OutputDevice()
{
	channel_count_ = channel_count;
}
