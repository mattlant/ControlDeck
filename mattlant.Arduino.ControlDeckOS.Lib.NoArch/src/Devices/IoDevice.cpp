// 
// 
// 

#include "IoDevice.h"

void IoDevice::begin_()
{
}

void IoDevice::process_()
{
}

void IoDevice::begin()
{
	if(!has_started_)
	{
		has_started_ = true;
		begin_();
	}
}

void IoDevice::process()
{
	process_();
}

