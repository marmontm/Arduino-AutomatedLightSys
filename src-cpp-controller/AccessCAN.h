// AccessCAN.h
#include <Arduino.h>
#include "BaseArduino.h"

#define ETALONNAGE_CAN		1024

// Prototypes
void SelectCAN_ADC3(void);
void SelectCAN_ADC2(void);
uint16_t ReadCAN_10b(void);
