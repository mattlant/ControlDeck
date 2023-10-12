// ControlProcessor.h

#ifndef BUTTONBOX_h
#define BUTTONBOX_h

#include "arduino.h"
#include "Controls/ButtonBase.h"
#include "LinkedList.h"

class ControlProcessor
{
protected:
	LinkedList* controls_;
	LinkedList* passive_devices_;
	LinkedList* active_devices_;
	uint8_t loop_delay_;
	void process_controls() const;
	void process_devices() const;


public:
	ControlProcessor(uint8_t loop_delay);

	virtual void begin();
	virtual void process();

	ControlProcessor* add_control(Control* control);
	ControlProcessor* add_passive_device(IoDevice* device);
	ControlProcessor* add_active_device(IoDevice* device);

};

#endif
