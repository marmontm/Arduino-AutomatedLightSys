#include "AccessPort.h"


void InitPort(void){
	DDRD = DDRD & ~B00110000;	//Entrées sur Port D
	DDRD = DDRD | BIT6;			//Sorties sur Port D
}

//Renvoie 0 pour LOW et 1 pour HIGH
bool hw_PBS1(void){
	bool bVal = hardware_NumInput(PIND, BIT4); //Nano: D4
	return bVal;
}

//Renvoie 0 pour LOW et 1 pour HIGH
bool hw_PBS2(void){
	bool bVal = hardware_NumInput(PIND, BIT5); //Nano: D5
	return bVal;
}

//Mode : 0=Low, 1=High, 2=Toggle
void hw_LED1(int iMode){	//Nano: D6
	if (iMode == 2)				//toggle
	{
		PORTD = PORTD ^ BIT6;
	}
	else if (iMode == 1)		//ON
	{
		PORTD = PORTD | BIT6;
	}
	else if (iMode == 0)		//OFF
	{
		PORTD = PORTD & ~BIT6;
	}
}
