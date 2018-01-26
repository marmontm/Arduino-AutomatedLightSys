#include "AccessTimer2.h"


void InitTimer2(void){
	TCCR2A = 0x00;
	TCCR2B = B00000111; //div horloge 1/1024 (T=64us)
	TCNT2 = 0; //comptage à 0 au départ
}

//activation/désactivation ISR sur débordement Timer2 (surveillance TOV2)
void EnableISR_Timer2(bool bEnable){
	if (bEnable){
		noInterrupts();
		TIMSK2 = 0x01;
		interrupts();
	}
	else if (!bEnable){
		noInterrupts();
		TIMSK2 = 0x00;
		interrupts();
	}
}
