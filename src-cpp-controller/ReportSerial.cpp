#include "ReportSerial.h"


//Accès aux variables globales
extern int iU_sensor;


//Afficher télémétrie du capteur de lumière
void DispDataLightSensor(int iOrder, int iLux, int iDutyCycle){
	/*Serial.print("U_capt: ");
	Serial.print((float)iU_sensor / 1000);
	Serial.print(" V");*/
	Serial.print("Consigne: ");
	Serial.print(iOrder);
	Serial.print(" %");
	Serial.print(", Lumiere: ");
	Serial.print(iLux);
	Serial.print(" %");
	Serial.print(", PWM: ");
	Serial.print(iDutyCycle);
	Serial.println(" %");
	//if (iU_sensor == 0){
	//	Serial.println("-- ERREUR D'ALIMENTATION --");
	//	Serial.println("Alimentation 5Vdc capteur manquante");
	//}
}

//Afficher mode ARU
void DispEmergencyStop(void){
	Serial.println("-- ARRET D'URGENCE --");
	Serial.println("Faire un Reset pour redemarrer.");
}