// F1_AutoMode.h
#include <Arduino.h>
#include "BaseArduino.h"
#include "AccessPort.h"
#include "AccessCAN.h"
#include "AccessTimer1.h"


#ifndef TSTATE_F1
#define TSTATE_F1
typedef enum {
	WaitingON,
	ON,
	WaitingOFF,
	OFF
}TState_F1;
#endif // !TSTATE_F1

#define MIN_LIGHT_INTENSITY		20

// Prototypes
void _F1_AutoMode(void);
void F1_ReadInputs(void);
void F1_StateGraph(void);
void F1_StateGraph_post(void);
void F1_WriteOutputs(void);
