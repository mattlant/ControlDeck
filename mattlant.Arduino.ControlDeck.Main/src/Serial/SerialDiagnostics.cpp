// 
// 
// 


#include "SerialDiagnostics.h"
#include <Arduino.h>

#define UNKNOWN_PIN 0xFF

uint8_t getPinMode(uint8_t pin)
{
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);

	// I don't see an option for mega to return this, but whatever...
	if (NOT_A_PIN == port) return UNKNOWN_PIN;

	// Is there a bit we can check?
	if (0 == bit) return UNKNOWN_PIN;

	// Is there only a single bit set?
	if (bit & bit - 1) return UNKNOWN_PIN;

	volatile uint8_t *reg, *out;
	reg = portModeRegister(port);
	out = portOutputRegister(port);

	if (*reg & bit)
		return OUTPUT;
	else if (*out & bit)
		return INPUT_PULLUP;
	else
		return INPUT;
}

int digitalReadOutputPin(uint8_t pin)
{
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	if (port == NOT_A_PIN)
		return LOW;

	return (*portOutputRegister(port) & bit) ? HIGH : LOW;
}


SerialDiagnostics_ SerialDiagnostics;

#define MAX_DIAG_PINS 16

void SerialDiagnostics_::send_pin_info()
{
	Serial.print("*p");
	Serial.print("[");
	for (byte i = 0; i < MAX_DIAG_PINS; i++)
	{
		Serial.print("{");
		Serial.print("\"p\":");
		Serial.print(i);
		Serial.print(",");

		byte mode = getPinMode(i);
		byte state = 0;
		if (mode == INPUT || mode == INPUT_PULLUP)
			state = digitalRead(i);
		else
			state = digitalReadOutputPin(i);

		Serial.print("\"m\":");
		Serial.print(mode);
		Serial.print(",");
		Serial.print("\"s\":");
		Serial.print(state);

		Serial.print("}");

		if (i != MAX_DIAG_PINS - 1)
			Serial.print(",");
	}

	Serial.print("]");
	Serial.print("p*");
}

void SerialDiagnostics_::send_pin_state()
{
	Serial.print("*s");
	Serial.print("[");
	for (byte i = 0; i < MAX_DIAG_PINS; i++)
	{
		byte mode = getPinMode(i);
		byte state = 0;
		if (mode == INPUT || mode == INPUT_PULLUP)
			state = digitalRead(i);
		else
			state = digitalReadOutputPin(i);

		Serial.print(state);

		if (i != MAX_DIAG_PINS - 1)
			Serial.print(",");
	}

	Serial.print("]");
	Serial.print("s*");
	Serial.println();
}

void SerialDiagnostics_::process()
{
	while (Serial.available() > 0)
	{
		const byte incomingChar = Serial.read(); // Read the incoming byte

		if (incomingChar == 'p')
		{
			send_pin_info();
		}
		else if (incomingChar == 's')
		{
			send_pin_state();
		}
	}
}
