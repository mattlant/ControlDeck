// 
// 
// 

#include "SerialTests.h"

#include <limits.h>

#define SERIAL_LED_PIN 4
#define JOYSTICK_LED_PIN 7

#define PAUSE_BUTTON_PIN 10
#define KILL_SWITCH_PIN 9

SerialTestsClass SerialTestSketch;

void SerialTestsClass::start_serial()
{
	if(is_serial_on_)
		return; //LOG

	Serial.begin(9600);
	is_serial_on_ = true;

	delay(1000);
	Serial.println("Serial started");

	this->update_leds();

}

void SerialTestsClass::stop_serial()
{
	if(!is_serial_on_)
		return; //LOG

	Serial.end();
	is_serial_on_ = false;

	this->update_leds();
}

void SerialTestsClass::connect_joystick()
{
	if(is_joystick_connected_)
		return; //LOG

	joystick_ = new Joystick_(3, JOYSTICK_TYPE_JOYSTICK, 4, 0, false, false, false, false, false, false, false, false, false, false, false);
	joystick_->begin();
	delay(200);
	is_joystick_connected_ = true;

	this->update_leds();
}

void SerialTestsClass::disconnect_joystick()
{
	if(!is_joystick_connected_ || joystick_ == nullptr)
		return; //LOG

	joystick_->end();
	delete joystick_;
	is_joystick_connected_ = false;

	this->update_leds();
}

void SerialTestsClass::update_leds()
{
	digitalWrite(SERIAL_LED_PIN, is_serial_on_);
	digitalWrite(JOYSTICK_LED_PIN, is_joystick_connected_);
}


void SerialTestsClass::flash_leds()
{
	for (int i = 0; i < 20; i++)
	{
		digitalWrite(SERIAL_LED_PIN, HIGH);
		digitalWrite(JOYSTICK_LED_PIN, LOW);
		delay(50);
		digitalWrite(SERIAL_LED_PIN, LOW);
		digitalWrite(JOYSTICK_LED_PIN, HIGH);
		delay(50);

	}
}

void SerialTestsClass::kill_check()
{
	if(digitalRead(KILL_SWITCH_PIN) == LOW)
	{
		flash_leds();

		//kill system
		stop_serial();
		delay(100);
		disconnect_joystick();
		delay(1000);
		start_serial();
		Serial.println("KILLED. Now entering LONG_MAX NOP delay loop");
		delay(LONG_MAX);
		exit(1);


	}
}


void SerialTestsClass::simulate_serial(unsigned long for_seconds)
{

	const unsigned long start_millis = millis();

	while(millis() - start_millis < for_seconds * 1000)
	{	kill_check();
		Serial.println(random(1000));
		delay(random(80));
	}

}

void SerialTestsClass::simulate_joystick(unsigned long for_seconds)
{
	const unsigned long start_millis = millis();

	while(millis() - start_millis < for_seconds * 1000)
	{
		kill_check();
		joystick_->pressButton(random(4));
		delay(random(200, 800));
	}

}


void SerialTestsClass::setup()
{
	pinMode(PAUSE_BUTTON_PIN, INPUT_PULLUP);
	pinMode(KILL_SWITCH_PIN, INPUT_PULLUP);
	pinMode(SERIAL_LED_PIN, OUTPUT);
	pinMode(JOYSTICK_LED_PIN, OUTPUT);

	update_leds();
}

void SerialTestsClass::loop()
{
	start_serial();
	simulate_serial(20);
	stop_serial();

	kill_check();
	delay(5000);

	connect_joystick();
	simulate_joystick(20);
	disconnect_joystick();

	kill_check();
	delay(5000);

	if(digitalRead(PAUSE_BUTTON_PIN) == LOW)
	{
		start_serial();
		delay(1000);
		while(true)
		{
			Serial.println("Test paused via button");
			delay(2000);
			if(digitalRead(PAUSE_BUTTON_PIN) == LOW)
			{
				Serial.println("Test resumed via button");
				stop_serial();
				delay(1000);
				break;
			}
		}
	}

}
