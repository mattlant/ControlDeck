// 
// 
// 

#include "oled_test.h"


void oled_test::setup()
{
}

void oled_test::loop()
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
