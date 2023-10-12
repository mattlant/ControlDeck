// 
// 
// 

#include "MatrixInputDevice.h"
#include "../util.h"

MatrixInputDevice::MatrixInputDevice(OutputDevice* rows_device, InputDevice* cols_device, byte row_count,
                                       byte col_count, byte row_channels[], byte col_channels[],
                                       byte active_state): InputDevice(),
                                                           row_channels_(row_channels), col_channels_(col_channels),
                                                           row_count_(row_count),
                                                           col_count_(col_count), rows_device_(rows_device),
                                                           cols_device(cols_device),
                                                           active_state_(active_state)
{
	state_ = new byte[channel_count_];
	last_process_millis = millis();
}


void MatrixInputDevice::begin_()
{
	rows_device_->begin();
	cols_device->begin();

	for (int row = 0; row < row_count_; ++row)
	{
		rows_device_->write(row_channels_[row], !active_state_);
	}
}

int MatrixInputDevice::read(byte input_id)
{
	if (input_id >= channel_count_)
	{
		DBG_PRINT("WARNING Matrix: Invalid input selected");
		DBG_PRINTLN(input_id);
		return 0;
	}
	return state_[input_id];
}

#define LOG_SCAN 0

void MatrixInputDevice::scan_keys()
{
	for (byte row = 0; row < row_count_; ++row)
	{
		rows_device_->write(row_channels_[row], active_state_);

		for (byte col = 0; col < col_count_; ++col)
		{
			byte input_id = row * col_count_ + col;

#if LOG_SCAN
			int curr_value = cols_device->read(col_channels_[col]);
			int old_state = state_[input_id];
			byte new_state = curr_value == active_state_;

			DBG_PRINTLN("matrix.scan.....");
			DBG_PRINT("--input=");
			DBG_PRINTLN(input_id);
			DBG_PRINT("--old_state=");
			DBG_PRINTLN(old_state);
			DBG_PRINT("--curr_value=");
			DBG_PRINTLN(old_state);
			DBG_PRINT("--new_state=");
			DBG_PRINTLN(old_state);
			delay(50);

#endif


			state_[input_id] = cols_device->read(col_channels_[col]) == active_state_;
		}

		rows_device_->write(row_channels_[row], !active_state_);
	}

#if LOG_SCAN
	delay(1000);
#endif
}

void MatrixInputDevice::process_()
{
	unsigned long current_millis = millis();
	if (current_millis - last_process_millis < MATRIX_MIN_TIME_BETWEEN_PROCESS)
		return;

	last_process_millis = current_millis;

	scan_keys();
}
