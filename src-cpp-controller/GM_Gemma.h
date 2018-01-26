// GM_Gemma.h
#include <Arduino.h>
#include "BaseArduino.h"
#include "AccessPort.h"
#include "AccessCAN.h"
#include "AccessTimer1.h"
#include "AccessTimer2.h"
#include "F1_AutoMode.h"
#include "F4_ManualMode.h"


#ifndef TSTATE_GM
#define TSTATE_GM
typedef enum {
	F1_Auto,
	WaitingAuto,
	F4_Manual,
	WaitingManual
}TState_GM;
#endif


// Prototypes
void _GM_Gemma(void);
void GM_ReadInputs(void);
void GM_StateGraph(void);
void GM_StateGraph_post(void);
void GM_WriteOutputs(void);
