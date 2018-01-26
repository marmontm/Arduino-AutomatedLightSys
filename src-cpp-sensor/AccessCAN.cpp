#include "AccessCAN.h"


void SelectCAN_ADC3(void){
	ADMUX = B01000011;	//ADC3: Photorésistance (capteur)
	ADCSRA = B10000100;
}

void SelectCAN_ADC2(void){
	ADMUX = B01000010;	//ADC2: Potentiomètre (consigne)
	ADCSRA = B10000100;
}

uint16_t ReadCAN_10b(void){ //bloquant
	uint8_t ui8CanL = 0;
	uint8_t ui8CanH = 0;
	uint16_t ui16Result = 0;

	ADCSRA = (ADCSRA | BIT6);
	do{
	} while ((ADCSRA & BIT6) == BIT6);
	ui8CanL = ADCL;
	ui8CanH = ADCH;
	ui16Result = ((uint16_t)ui8CanH << 8) + ui8CanL;

	return ui16Result;
}
