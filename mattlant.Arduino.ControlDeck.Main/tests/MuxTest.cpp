#ifndef ARDUINO_SIM
#include "src/SerialDiagnostics.h"

#endif
#include "MuxTest.h"
#include "src/Devices/MuxInputDevice.h"

namespace mux_test
{

	byte select_pins[4] = { 5, 6, 7, 8 };
	MuxInputDevice* m = 0;


	void setup()
	{
		Serial.begin(115200);
		m->begin();
	}

	void loop()
	{
		Serial.print("Mux: ");
		for (byte i = 0; i < 16; i++)
		{
			int input = m->read(i);
			Serial.print(input);
			Serial.print(",");
		}
		delay(250);
	}
}
