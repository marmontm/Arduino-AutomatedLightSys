#include "LightSensor.h"

void setup() {
	Serial.begin(9600);
	Serial.print("Starting... ");
	RF_initSensorPart();
	SelectCAN_ADC3();
	// Fin init
	delay(1000);
	Serial.println("OK");
}

uint16_t ui16CANvalue = 0;

void loop() {
	ui16CANvalue = ReadCAN_10b();
	RF_sendToMCU(1506, ui16CANvalue);
	delay(10);
}
