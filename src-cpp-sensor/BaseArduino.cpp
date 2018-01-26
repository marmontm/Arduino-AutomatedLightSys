#include "BaseArduino.h"


// Affectation � une sortie num�rique : 0=0L, 1=1L, 2=Toggle
void hardware_NumOutput(int iMode, uint8_t hw_PORT, uint8_t hw_BYTE){
	if (iMode == 2)				//toggle
	{
		hw_PORT = hw_PORT ^ hw_BYTE;
	}
	else if (iMode == 1)		//ON
	{
		hw_PORT = hw_PORT | hw_BYTE;
	}
	else if (iMode == 0)		//OFF
	{
		hw_PORT = hw_PORT & ~hw_BYTE;
	}
}

// Lecture d'une entr�e num�rique : Renvoie 0 ou 1
bool hardware_NumInput(uint8_t hw_PIN, uint8_t hw_BIT){
	bool bVal = ((hw_PIN & hw_BIT) == hw_BIT);
	return bVal;
}

// Conversion capteur vers mesure : prend valeur CAN et renvoie un nombre entier entre 0 et un maximum (proportionnalit�)
int ConvCAN2Nombre(uint16_t ui16_ValConv, int iMin, int iMax, int iEtalonnage){
	int iValeurConvertie = (int)(((float)(iMax - iMin) / (iEtalonnage - 1))*ui16_ValConv + iMin);
	return iValeurConvertie;
}

// Re�oit un nombre entre 0 et un max, puis renvoie le pourcentage associ� (entier allant de 0 � 100)
int ConvNumber2Percent(int iVal, int iVal_max){
	int iRetPercent = (int)(100 * (float)(iVal / iVal_max));
	return iRetPercent;
}

// Re�oit un pourcentage et un nombre max, puis renvoie le nombre associ� � ce pourcentage (entier allant de 0 � iVal_max)
int ConvPercent2Number(int iPercent, int iVal_max) {
	int iRetNumber = (int)((float)iPercent*iVal_max / 100);
	return iRetNumber;
}
