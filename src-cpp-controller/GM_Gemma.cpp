#include "GM_Gemma.h"


TState_GM StateGM = WaitingAuto;
TState_GM StateGM_old = StateGM;

extern TState_F4 StateF4;
extern TState_F1 StateF1;
extern int iMeasureLux;
extern int iOrderLux;


// Entrées
bool iex_bS1 = false;
bool iex_bS2 = false;
int iex_iLux = 0;
int iex_iOrderLux = 0;

// Sorties
bool qex_bLED = false;
bool qex_bEnLight = false;
bool qex_bEnableTimer = false;
bool qex_bEnableLEDblink = false;

// Variables
int vx_iDutyCycle = 0;
int vx_iDutyCycle_old = vx_iDutyCycle;
int vx_iTimeStart = 0;
int vx_iTime = 0;
bool mx_bF1 = false;
bool mx_bF4 = false;


void _GM_Gemma(void) {
	GM_ReadInputs();
	GM_StateGraph();
	GM_StateGraph_post();
	GM_WriteOutputs();
}

void GM_ReadInputs(void) {
	iex_bS2 = hw_PBS2();
	iex_iLux = iMeasureLux;
	iex_iOrderLux = iOrderLux;
}

void GM_StateGraph(void) {
	switch (StateGM)
	{
	case WaitingAuto:
		if (!iex_bS2)
		{
			StateGM = F1_Auto;
		}
		break;
	case F1_Auto:
		if (iex_bS2)
		{
			StateGM = WaitingManual;
		}
		break;
	case WaitingManual:
		if (!iex_bS2)
		{
			StateGM = F4_Manual;
		}
		break;
	case F4_Manual:
		if (iex_bS2)
		{
			StateGM = WaitingAuto;
		}
		break;
	}
}

void GM_StateGraph_post(void) {
	switch (StateGM)
	{
	case WaitingAuto:
		mx_bF1 = false;
		mx_bF4 = false;
		qex_bLED = false;
		break;
	case F1_Auto:
		mx_bF1 = true;
		mx_bF4 = false;
		qex_bLED = true;
		break;
	case WaitingManual:
		mx_bF1 = false;
		mx_bF4 = false;
		qex_bLED = false;
		break;
	case F4_Manual:
		mx_bF1 = false;
		mx_bF4 = true;
		qex_bLED = true;
		break;
	}
}

void GM_WriteOutputs(void) {
	if (StateGM!=StateGM_old)
	{
		//Etats initiaux
		if (mx_bF4)
		{
			StateF4 = Init;
		}
		if (mx_bF1)
		{
			EnableISR_Timer2(true);
			StateF1 = WaitingON;
		}
		else
		{
			EnableISR_Timer2(false);
		}
		//Actionneurs
		hw_LED1(qex_bLED);
		//Affectation état précédent
		StateGM_old = StateGM;
	}
}