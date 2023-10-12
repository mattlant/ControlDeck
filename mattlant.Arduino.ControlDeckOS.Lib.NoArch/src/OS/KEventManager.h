// KEventManager.h

#ifndef _KEVENTMANAGER_h
#define _KEVENTMANAGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class KEventManagerClass
{
 protected:


 public:
	void init();
};

extern KEventManagerClass KEventManager;

#endif

