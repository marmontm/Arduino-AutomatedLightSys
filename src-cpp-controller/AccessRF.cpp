#include "AccessRF.h"


void RF_initOperativePart(void){
	Mirf.cePin = 8; // CE sur D8
	Mirf.csnPin = 7; // CSN sur D7
	Mirf.spi = &MirfHardwareSpi; // on utilise le port SPI
	Mirf.init();
	Mirf.channel = 74; // Canal utilisé : 74 (0-127)
	Mirf.payload = sizeof(unsigned long); // = 4 (octets). On veut envoyer 2 fois 16 bits
	Mirf.config();
	Mirf.setRADDR((byte *)"sysc0"); // adresse expediteur (5 octets)
	Mirf.setTADDR((byte *)"sens1"); // adresse destinataire (5 octets)
	Serial.println("RF pret.");
}

uint16_t RF_requestSensor(uint16_t ui16CodeValue, uint16_t ui16RetValue_old){
	//---Variables locales---//
	unsigned long iTimeStart = millis();
	unsigned long iTimePing = 0;
	uint32_t ui32SendValue = 0x00000000; //octets a envoyer (code + valeur à 0)
	uint16_t ui16RetCodeValue = 0x0000; //code valeur recu
	uint16_t ui16RetValue = 0x0000; //valeur recue (CAN)
	byte BReceivedValue[Mirf.payload]; //on declare le tableau de transfert sur 4 unites (octets)

	//---Envoi des donnees---//
	ui32SendValue = (uint32_t)ui16CodeValue;
	Mirf.send((byte *)&ui32SendValue); // on envoie les 4 octets : [3:2]ReserveAuCAN, [1:0]CodeValeur)
	while (Mirf.isSending()); // on attend que le message soit envoye
	Serial.print("Requete ");
	Serial.print(ui16CodeValue);
	Serial.print("... ");
	delay(10); // attente de 10ms

	//---Attente de la reponse---//
	while (!Mirf.dataReady()){ // On attend de recevoir quelque chose
		if ((millis() - iTimeStart) > 1000) { // Si on attend depuis plus d'une seconde
			Serial.println("Echec."); // on abandonne la connexion
			return ui16RetValue_old; // on quitte la fonction avec la valeur précédente
		}
	}

	//---Reception des donnees---//
	Mirf.getData((byte *)&BReceivedValue); // on recupere le message du capteur
	iTimePing = millis() - iTimeStart; // on calcule le temps de latence (ping)
	ui16RetCodeValue = (uint16_t)(((uint16_t)BReceivedValue[1] << 8) + (uint16_t)BReceivedValue[0]);

	//---Traitement des donnees suivant le code envoye---//
	if (ui16RetCodeValue == (ui16CodeValue * 2)){ // si code correct (CodeEnvoye * 2), on prend la valeur recue (->CAN)
		ui16RetValue = (uint16_t)(((uint16_t)BReceivedValue[3] << 8) + (uint16_t)BReceivedValue[2]);
		Serial.print("CAN: ");
		Serial.print(ui16RetValue);
	}
	else // si le code est incorrect, on affecte la valeur précédente
	{
		ui16RetValue = ui16RetValue_old;
		Serial.print("Code incorrect.");
	}
	Serial.print(" (Ping: ");
	Serial.print(iTimePing); // on affiche le temps de latence (ping)
	Serial.println("ms)");
	//delay(1000);
	return ui16RetValue;
}
