#include "F4_ManualMode.h"


TState_F4 StateF4;
TState_F4 StateF4_old = Normal;

// Entrées
extern bool iex_bS1;
extern bool iex_bS2;

// Sorties
extern bool qex_bLED;
extern bool qex_bEnableTimer;
extern bool qex_bEnableLEDblink;
extern int vx_iDutyCycle;
extern int vx_iDutyCycle_old;
extern int vx_iTimeStart;
extern int vx_iTime;

// Variables
bool bInit_OK = false;

void _F4_ManualMode(void) {
	F4_ReadInputs();
	F4_StateGraph();
	F4_StateGraph_post();
	F4_WriteOutputs();
}

void F4_ReadInputs(void) {
	iex_bS1 = hw_PBS1();
}

void F4_StateGraph(void) {
	switch (StateF4)
	{
	case Init:
		if (bInit_OK)
		{
			StateF4 = Normal;
		}
		break;
	case Normal:
		if (iex_bS1)
		{
			StateF4 = TimeCount;
		}
		break;
	case TimeCount:
		if ((vx_iTime >= 1000) || (vx_iDutyCycle >= 95))
		{
			StateF4 = LightReset;
		}
		else if ((!iex_bS1) && (vx_iTime < 1000))
		{
			StateF4 = LightPlus;
		}
		break;
	case LightReset:
		if (!iex_bS1)
		{
			StateF4 = Normal;
		}
		break;
	case LightPlus:
		if (!iex_bS1)
		{
			StateF4 = Normal;
		}
		break;
	}
}

void F4_StateGraph_post(void) {
	if (StateF4 != StateF4_old)
	{
		switch (StateF4)
		{
		case Init:
			bInit_OK = true;
			//Serial.println("Init");
			break;
		case Normal:
			//Serial.println("Normal");
			break;
		case TimeCount:
			///Compter une seconde (durée d'appui sur S1)
			vx_iTimeStart = millis();
			//Serial.println("TimeCount");
			break;
		case LightReset:
			vx_iDutyCycle = 0;
			//Serial.println("LightReset");
			break;
		case LightPlus:
			vx_iDutyCycle = vx_iDutyCycle + 10;
			//Serial.println("LightPlus");
			break;
		}
		StateF4_old = StateF4;
	}
}

void F4_WriteOutputs(void) {
	//Sortie PWM
	if (vx_iDutyCycle != vx_iDutyCycle_old){
		OCR1B = ConvPercent2Number(vx_iDutyCycle, ETALONNAGE_PWM1 - 1);
		vx_iDutyCycle_old = vx_iDutyCycle;
	}
	vx_iTime = millis() - vx_iTimeStart;
}