// Sketch.h

#ifndef _SKETCH_h
#define _SKETCH_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SketchBase
{
 public:
	virtual void setup();
	virtual void loop();
};


#endif

