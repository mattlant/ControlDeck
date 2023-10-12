/*
 Name:		mattlant.h
 Created:	10/15/2023 10:24:24 AM
 Author:	mattl
 Editor:	http://www.visualmicro.com
*/

#ifndef _mattlant_h
#define _mattlant_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

namespace ml
{

void setup();
void loop();

}

#endif

