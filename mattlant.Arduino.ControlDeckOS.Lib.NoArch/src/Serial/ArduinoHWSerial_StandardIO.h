// SerialStdIO.h

#ifndef _ARD_PLTFRM_HWSERIALIO_h
#define _ARD_PLTFRM_HWSERIALIO_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "../OS/StdIOBase.h"

class HardwareSerialInput : public StandardInput
{
public:
	HardwareSerialInput(int speed)
	{
		Serial.begin(speed);
	};

	HardwareSerialInput() : HardwareSerialInput(115200)
	{
	};

	char readChar() override
	{
		return Serial.read();
	}

	bool available() override
	{
		return Serial.available();
	}
};

class HardwareSerialOutput : public StandardOutput
{
public:
	HardwareSerialOutput(int speed)
	{
		Serial.begin(speed);
	};

	HardwareSerialOutput() : HardwareSerialOutput(115200)
	{
	};

	void print(const char* str) override
	{
		Serial.print(str);
	}

	void print(char c) override
	{
		Serial.print(c);
	}

	void println(const char* str) override
	{
		Serial.println(str);
	}

	void println() override
	{
		Serial.println();
	}

	void print(int c) override
	{
		Serial.print(c);
	}

	void print(long c) override
	{
		Serial.print(c);
	}

	void print(unsigned long c) override
	{
		Serial.print(c);
	}

	void println(float value) override
	{
		Serial.print(value);
	}
};

#endif
