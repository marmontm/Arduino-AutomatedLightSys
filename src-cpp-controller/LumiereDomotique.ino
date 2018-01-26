/*
 Project:	Projet ER2 - Lumière Domotique
 Created:	28/04/2016 09:39:45
 Version:	2.1_Release_2016-05-26
 Author:	Alan BELLO, Maxime MARMONT
 GUID:		{D1F79C43-FCC3-410B-9141-6C2A45446CAA}
 Language:	Comments in French
 Tools:		Visual Studio 14.0, Visual Micro 1603.1, IDE Arduino 1.6
*/



//ENTETE
#include "LumiereDomotique.h"

//GLOBALES
uint16_t ui16CAN_ADC3_value = 0;
uint16_t ui16CAN_ADC3_value_old = ui16CAN_ADC3_value;
uint16_t ui16CAN_ADC2_value = 0;
int iOrderLux = 0;
int iOrderLux_old;
int iMeasureLux = 0;
int iMeasureLux_old;
int iU_sensor = 0;
int iU_sensor_old = iU_sensor;
int iNbOVF_Timer2 = 0;
int iDelay_start = 0;
int iDelay_cnt = 0;
int iDelay_RFstart = 0;
int iDelay_RFcnt = 0;
bool bARUmode = false;

extern int vx_iDutyCycle;
extern bool mx_bF1;
extern bool mx_bF4;

//INTERRUPTIONS
//Interruption sur Timer2, compte 61 débordements correspondant à une demie-période de 1s
ISR(TIMER2_OVF_vect){
	TCNT2 = 0;
	iNbOVF_Timer2++;
	if (iNbOVF_Timer2 >= 61)
	{
		hw_LED1(2);
		iNbOVF_Timer2 = 0;
	}
}

//FCT MICRO
void setup() {
	InitPort();
	hw_LED1(1);
	Serial.begin(9600);
	Serial.println();
	Serial.print("Starting... ");
	// Initialisation des timers
	InitPWM1();
	InitTimer2();
	EnableISR_Timer2(false);
	RF_initOperativePart();
	// Fin de l'initialisation, attente de 1s avant début du programme
	delay(100);
	hw_LED1(0);
	delay(1000);
	iDelay_start = millis();
	Serial.println("OK");
}


void loop() {
	// Récupération des valeurs des entrées analogiques
	iDelay_RFcnt = millis() - iDelay_RFstart;
	if ((iDelay_RFcnt >= RF_REFRESH))
	{
		ui16CAN_ADC3_value = RF_requestSensor(1506, ui16CAN_ADC3_value_old); // on interroge le capteur via RF
		ui16CAN_ADC3_value_old = ui16CAN_ADC3_value;
		iDelay_RFcnt = 0;
		iDelay_RFstart = millis();
	}
	SelectCAN_ADC2();
	ui16CAN_ADC2_value = ReadCAN_10b();
	// Analyse (conversion vers des valeurs exploitables)
	iMeasureLux = 100 - ConvCAN2Nombre(ui16CAN_ADC3_value, 0, 100, ETALONNAGE_CAN);
	iOrderLux = ConvCAN2Nombre(ui16CAN_ADC2_value, 0, 100, ETALONNAGE_CAN);
	iU_sensor = ConvCAN2Nombre(ui16CAN_ADC3_value, 0, 5000, ETALONNAGE_CAN);
	///// MODE ARRET D'URGENCE (ARU) ////////////////////////////////
	if (hw_PBS1() && hw_PBS2()){
		bARUmode = true;
		EnableISR_Timer2(false);
		hw_LED1(0);
		OCR1B = 0;
		DispEmergencyStop();
	}	// FIN ARU //////////////////////////////////////////////////
	else if (!bARUmode) {
		//-----Gestion des modes de fonctionnement-----//
		_GM_Gemma();
		//--F1 Mode Auto--//
		if (mx_bF1)
		{
			_F1_AutoMode();
		}
		//--F4 Mode Manuel--//
		if (mx_bF4)
		{
			_F4_ManualMode();
		}
		//Retour Serial
		iDelay_cnt = millis() - iDelay_start;
		if ((iDelay_cnt >= SERIAL_DISP_REFRESH))
		{
			DispDataLightSensor(iOrderLux, iMeasureLux, vx_iDutyCycle);
			iDelay_cnt = 0;
			iDelay_start = millis();
		}
	}

}
