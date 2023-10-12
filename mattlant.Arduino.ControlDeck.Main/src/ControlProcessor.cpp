#include "ControlProcessor.h"
#include "util.h"

ControlProcessor::ControlProcessor(const uint8_t loop_delay): loop_delay_(loop_delay)
{
	controls_ = new LinkedList();
	passive_devices_ = new LinkedList();
	active_devices_ = new LinkedList();
}

void ControlProcessor::begin()
{
	int i = 0;
	DBG_PRINTLN("ControlProcessor.begin");

	DBG_PRINTLN("-- executing begin on active devices.");
	const LinkedListItem* item = static_cast<const LinkedListItem*>(active_devices_->getHead());
	while (item != nullptr)
	{
		DBG_PRINT("---- begin active device: ");
		DBG_PRINTLN(i++);
		auto* device = static_cast<IoDevice*>(item->data);
		device->begin();
		item = static_cast<const LinkedListItem*>(item->next);
	}

	i = 0;
	DBG_PRINTLN("-- executing begin on passive devices.");
	item = static_cast<const LinkedListItem*>(passive_devices_->getHead());
	while (item != nullptr)
	{
		DBG_PRINT("---- begin passive device: ");
		DBG_PRINTLN(i++);
		auto* device = static_cast<IoDevice*>(item->data);
		device->begin();
		item = static_cast<const LinkedListItem*>(item->next);
	}

	i = 0;
	DBG_PRINTLN("-- executing setup on controls.");
	item = static_cast<const LinkedListItem*>(controls_->getHead());
	while (item != nullptr)
	{
		DBG_PRINT("---- setup control: ");
		DBG_PRINTLN(i++);
		const auto button = static_cast<Control*>(item->data);
		button->setup();
		item = static_cast<const LinkedListItem*>(item->next);
	}
}

void ControlProcessor::process_controls() const
{
	const LinkedListItem* item = static_cast<const LinkedListItem*>(controls_->getHead());
	while (item != nullptr)
	{
		auto* button = static_cast<Control*>(item->data);
		button->process();
		item = static_cast<const LinkedListItem*>(item->next);
	}
}

void ControlProcessor::process_devices() const
{
	const LinkedListItem* item = static_cast<const LinkedListItem*>(active_devices_->getHead());
	while (item != nullptr)
	{
		auto* device = static_cast<IoDevice*>(item->data);
		device->process();
		item = static_cast<const LinkedListItem*>(item->next);
	}
}

void ControlProcessor::process()
{
	process_devices();
	process_controls();
	if (loop_delay_ > 0)
		delay(loop_delay_);
}

ControlProcessor* ControlProcessor::add_control(Control* control)
{
	controls_->append(control);
	return this;
}

ControlProcessor* ControlProcessor::add_passive_device(IoDevice* device)
{
	passive_devices_->append(device);
	return this;
}

ControlProcessor* ControlProcessor::add_active_device(IoDevice* device)
{
	active_devices_->append(device);
	return this;
}
