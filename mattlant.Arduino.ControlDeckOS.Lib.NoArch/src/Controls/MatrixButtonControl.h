//// MatrixButtonControl.h
//
//#ifndef _MATRIXBUTTONCONTROL_h
//#define _MATRIXBUTTONCONTROL_h
//
//#if defined(ARDUINO) && ARDUINO >= 100
//	#include "arduino.h"
//#else
//	#include "WProgram.h"
//#endif
//#include "src/ButtonBase.h"
//
//class MatrixButtonControlClass : public ButtonBase
//{
//	//TODO: inherit from a bare "Control" type base class
// public:
//	MatrixButtonControlClass(InputDevice* rows_channel, OutputChannel* output_channel)
//		: ButtonBase(rows_channel, 0, output_channel, 0), rows_device_(rows_channel), cols_device(cols_channel)
//	{
//
//	}
//
//	void map(int input_id, int output_id);
//protected:
//	InputDevice* rows_device_;
//	InputDevice* cols_device;
//};
//
//extern MatrixButtonControlClass MatrixButtonControl;
//
//#endif
//
