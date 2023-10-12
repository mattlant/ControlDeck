// SerialDiagnostics.h

#ifndef _SERIALDIAGNOSTICS_h
#define _SERIALDIAGNOSTICS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SerialDiagnostics_
{
 protected:


 public:
	bool verbose = false;
	void send_pin_info();
	void send_pin_state();
	void process();
};

extern SerialDiagnostics_ SerialDiagnostics;

#endif

