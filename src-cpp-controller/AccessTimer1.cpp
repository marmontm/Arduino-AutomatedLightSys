#include "AccessTimer1.h"


void InitPWM1(void) {
	TCCR1A = B00100001;		//Fast PWM 8 bits, Canal B
	TCCR1B = B00001100;		//Clk div 1/256
	TCCR1C = 0x00;			//inutilisé
	DDRB = DDRB | BIT2;		//Nano: D10
	OCR1B = 0;				//Rapport de 0% au départ
}