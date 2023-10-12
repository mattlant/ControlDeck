// MatrixInputChannel.h

#ifndef MATRIXINPUTCHANNEL_h
#define MATRIXINPUTCHANNEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "InputDevice.h"
#include "OutputDevice.h"

#define MATRIX_MAX_INPUT_DETECT 3
#define MATRIX_MIN_TIME_BETWEEN_PROCESS 1

class MatrixInputDevice : public InputDevice
{
public:
	MatrixInputDevice(OutputDevice* rows_device, InputDevice* cols_device, byte row_count, byte col_count, byte row_channels[], byte col_channels[], byte active_state = false);

	void begin_() override;
	void process_() override;

	int read(byte input_id) override;
	virtual void scan_keys();

protected:
	byte* row_channels_;
	byte* col_channels_;
	byte* state_;
	unsigned long last_process_millis;
	byte row_count_;
	byte col_count_;
	OutputDevice* rows_device_;
	InputDevice* cols_device;
	byte active_state_;
};


#endif
