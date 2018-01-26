#include "F1_AutoMode.h"


TState_F1 StateF1;
TState_F1 StateF1_old = OFF;

// Entrées
extern int iex_iLux;
extern int iex_iOrderLux;
extern bool iex_bS1;

// Sorties
extern bool qex_bEnLight;

// Variables
extern int vx_iDutyCycle;
extern int vx_iDutyCycle_old;
extern uint16_t ui16CAN_ADC3_value;
extern uint16_t ui16CAN_ADC2_value;

void _F1_AutoMode(void) {
	F1_ReadInputs();
	F1_StateGraph();
	F1_StateGraph_post();
	F1_WriteOutputs();
}

void F1_ReadInputs(void) {
	iex_bS1 = hw_PBS1();
}

void F1_StateGraph(void) {
	switch (StateF1){
	case WaitingON:
		if (!iex_bS1){
			StateF1 = ON;
		}
		break;
	case ON:
		if (iex_bS1){
			StateF1 = WaitingOFF;
		}
		break;
	case WaitingOFF:
		if (!iex_bS1){
			StateF1 = OFF;
		}
		break;
	case OFF:
		if (iex_bS1){
			StateF1 = WaitingON;
		}
		break;
	}
}

void F1_StateGraph_post(void) {
	if (StateF1 != StateF1_old){
		switch (StateF1){
		case WaitingON:
			qex_bEnLight = true;
			break;
		case ON:
			qex_bEnLight = true;
			break;
		case WaitingOFF:
			qex_bEnLight = false;
			break;
		case OFF:
			qex_bEnLight = false;
			break;
		}
		StateF1_old = StateF1;
	}
}

void F1_WriteOutputs(void) {
	// Calcul du rapport cyclique à appliquer
	if (((iex_iOrderLux - iex_iLux) >= 20) && qex_bEnLight){			// --Poubelle--((iex_iOrderLux - iex_iLux) >= MIN_LIGHT_INTENSITY) && 
		
		vx_iDutyCycle = iex_iOrderLux - iex_iLux;
	}
	else
	{
		vx_iDutyCycle = 0;
	}
	// Application du rapport cyclique sur la sortie PB2
	if (vx_iDutyCycle != vx_iDutyCycle_old){
		OCR1B = ConvPercent2Number(vx_iDutyCycle, (ETALONNAGE_PWM1 - 1));
		vx_iDutyCycle_old = vx_iDutyCycle;
	}
}