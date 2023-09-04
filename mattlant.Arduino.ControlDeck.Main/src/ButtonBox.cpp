// 
// 
// 

#include "ButtonBox.h"



ButtonBox::ButtonBox(ButtonBase* buttons[], int button_count, uint8_t loop_delay): buttons_(buttons),
	button_count_(button_count), loop_delay_(loop_delay)
{
}

void ButtonBox::setup()
{
	joystick_->begin();

	for(int i = 0; i < button_count_; i++)
		buttons_[i]->set_joystick(*joystick_);


	for(int i = 0; i < button_count_; i++)
		buttons_[i]->setup();

}

void ButtonBox::process()
{
	for(int i = 0; i < button_count_; i++)
		buttons_[i]->process();

	delay(loop_delay_);

}
