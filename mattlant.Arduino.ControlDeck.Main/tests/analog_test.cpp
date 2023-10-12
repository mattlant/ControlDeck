// 
// 
// 

#include "analog_test.h"

byte x_pin = A0;
byte y_pin = A1;

byte x_led_pin = 7;
byte y_led_pin = 9;

int x_val;
int y_val;

void analog_test::setup()
{
}

void analog_test::loop()
{
	// read the value from the sensor:
	x_val = analogRead(x_pin);
	y_val = analogRead(y_pin);

	Serial.print("X/Y:");
	Serial.print(x_val);
	Serial.print("/");
	Serial.print(y_val);
	Serial.println();

	delay(100);

}
