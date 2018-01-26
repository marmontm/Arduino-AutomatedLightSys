// F4_ManualMode.h
#include <Arduino.h>
#include "BaseArduino.h"
#include "AccessPort.h"
#include "AccessCAN.h"
#include "AccessTimer1.h"


#ifndef TSTATE_F4
#define TSTATE_F4
typedef enum {
	Init,
	Normal,
	TimeCount,
	LightReset,
	LightPlus
}TState_F4;
#endif // !TSTATE_F4


// Prototypes
void _F4_ManualMode(void);
void F4_ReadInputs(void);
void F4_StateGraph(void);
void F4_StateGraph_post(void);
void F4_WriteOutputs(void);
