// JoystickOutputChannel.h

#ifndef HIDJOYSTICKOUTPUTCHANNEL_h
#define HIDJOYSTICKOUTPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <Joystick.h>
#include "OutputDevice.h"

#define	HAT 1000
#define	XAxis 128
#define	YAxis 129
#define	ZAxis 130
#define	XAxis2 131
#define	YAxis2 132
#define	ZAxis2 133

struct AxisChannelMap
{
	byte x;
	byte y;
	byte z;
};

struct AxisValues
{
	int x;
	int y;
	int z;
};
struct AxisRange
{
	int x_min;
	int y_min;
	int z_min;
	int x_max;
	int y_max;
	int z_max;
};

class JoystickOutputDevice : public OutputDevice
{
private:

public:
	JoystickOutputDevice(uint8_t hid_report_id, byte button_count, bool use_x_axis = false, bool use_y_axis = false,
	                     bool use_z_axis = false);

	void begin_() override;

	void write(byte button_id, int value) override;

	void setup_axis(byte axis_number, int min_range, int max_range);
	Joystick_* joystick_;

protected:
	byte* button_channel_map_; //int array
	byte* button_count_; //int array
	AxisChannelMap axis_channels_; //int array
	bool use_x_axis_;
	bool use_y_axis_;
	bool use_z_axis_;
	AxisRange axis1_range_;
	uint8_t hid_report_id_;
};

#endif
