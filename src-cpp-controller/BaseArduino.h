#pragma once

#include <Arduino.h>

#ifndef MASK_8BIT_H
#define MASK_8BIT_H

#define BIT0		B00000001
#define BIT1		B00000010
#define BIT2		B00000100
#define BIT3		B00001000
#define BIT4		B00010000
#define BIT5		B00100000
#define BIT6		B01000000
#define BIT7		B10000000

#endif // MASK_8BIT_H

//Prototypes
void hardware_NumOutput(int iMode, uint8_t hw_PORT, uint8_t hw_BYTE);
bool hardware_NumInput(uint8_t hw_PIN, uint8_t hw_BIT);
int ConvCAN2Nombre(uint16_t ui16_ValConv, int iMin, int iMax, int iEtalonnage);
int ConvNumber2Percent(int iVal, int iVal_max);
int ConvPercent2Number(int iPercent, int iVal_max);
