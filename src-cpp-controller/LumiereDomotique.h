//Bibliothèque Arduino
#include <Arduino.h>	
//Fichiers pour Arduino
#include "BaseArduino.h"
//Accès aux composants
#include "AccessCAN.h"
#include "AccessPort.h"
#include "AccessTimer1.h"
#include "AccessTimer2.h"
#include "AccessRF.h"
//Fonctions du projet
#include "ReportSerial.h"
#include "GM_Gemma.h"
#include "F4_ManualMode.h"
#include "F1_AutoMode.h"

//Constantes globales
#define SERIAL_DISP_REFRESH		1000	//temps en ms
#define RF_REFRESH	1000				//temps en ms
#define DEBUG_MODE