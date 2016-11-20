#include <Arduino.h>
#include "hardware.h"
#include "esc.h"
float speed;

int throttle_val;
int rawIn;

//Thresholds
float minPedalVoltage = 240.0;
int maxPedalVoltage = 890.0;

Esc myEsc;

void setup(){
	Serial.begin(9600);
  delay(1000);

  //Initialize ESC
  myEsc.begin();
  delay(15000);
  
}

void loop(){
  //Read Throttle Input
 	rawIn = analogRead(A10);
	Serial.print("Raw In: ");
	Serial.println(rawIn);

  //Convert to a value to send to ESC
	throttle_val = ((rawIn - minPedalVoltage) / (maxPedalVoltage - minPedalVoltage)) * 180;
	Serial.print("Throttle Value: ");
	Serial.println(throttle_val);

	if (throttle_val <= 180 && throttle_val >= 0){
		myEsc.write(throttle_val);
	}
	else if (throttle_val > 180){
		myEsc.write(180);
	}
	else{
		myEsc.write(0);
	}
}
