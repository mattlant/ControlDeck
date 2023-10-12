// EmKMod.h

#ifndef _EMKMOD_h
#define _EMKMOD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class CDKernel;

class KModule
{
 protected:


 public:
	virtual void init() = 0;
	virtual void exit() = 0;
};


class BootMessageMod
{
 protected:


 public:
	void init();
	void exit();
};

#endif

