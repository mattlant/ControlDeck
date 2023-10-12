// KExecutable.h

#ifndef _KEXECUTABLE_h
#define _KEXECUTABLE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "KernelCommon.h"

struct KExecutableParams
{
	
};

class KExecutable
{
 protected:

 public:
	virtual TaskExecutionResult execute(int param) = 0;
};


#endif

			   