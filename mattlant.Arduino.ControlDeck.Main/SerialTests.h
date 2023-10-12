// SerialTests.h

#ifndef _SERIALTESTS_h
#define _SERIALTESTS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "src/Sketch.h"

#include <Joystick.h>

class SerialTestsClass : public SketchBase
{
	Joystick_* joystick_ = nullptr;

	bool is_serial_on_ = false;
	bool is_joystick_connected_ = false;

	void start_serial();
	void stop_serial();
	void connect_joystick();
	void disconnect_joystick();
	void update_leds();
	void flash_leds();
	void kill_check();
	void simulate_serial(unsigned long for_seconds);
	void simulate_joystick(unsigned long for_seconds);

public:
	void setup() override;
	void loop() override;
};

extern SerialTestsClass SerialTestSketch;

#endif
