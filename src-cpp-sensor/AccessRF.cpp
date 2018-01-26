#include "AccessRF.h"


void RF_initSensorPart(void){
	Mirf.cePin = 8; // CE sur D8
	Mirf.csnPin = 7; // CSN sur D7
	Mirf.spi = &MirfHardwareSpi; // on utilise le port SPI
	Mirf.init();
	Mirf.channel = 74; // Canal utilisé : 74 (0-127)
	Mirf.payload = sizeof(unsigned long); // = 4 (octets). On veut envoyer 2 fois 16 bits
	Mirf.config();
	Mirf.setRADDR((byte *)"sens1"); // adresse expediteur (5 octets)
	Mirf.setTADDR((byte *)"sysc0"); // adresse destinataire (5 octets)
	Serial.println("RF pret.");
}

void RF_sendToMCU(uint16_t ui16CodeValue, uint16_t ui16Value) {
	//---Variables locales---//
	unsigned long iTimeStart = 0;
	unsigned long iTimePing = 0;
	uint32_t ui32SendValue = 0x00000000; //octets a envoyer (code + valeur à 0)
	uint16_t ui16RetCodeValue = 0x0000; //code valeur recu
	byte BReceivedValue[Mirf.payload]; //on declare le tableau de transfert sur 4 unites (octets)

	if (!Mirf.isSending() && Mirf.dataReady()) { // Si un message est recu
		iTimeStart = millis();
		Mirf.getData((byte *)&BReceivedValue); // on recupere le message
		iTimePing = millis() - iTimeStart; // on calcule le temps de latence (ping)
		ui16RetCodeValue = (uint16_t)(((uint16_t)BReceivedValue[1] << 8) + (uint16_t)BReceivedValue[0]);
		Serial.print("RxCode: ");
		Serial.print(ui16RetCodeValue);
		Serial.print(" (Ping: ");
		Serial.print(iTimePing);
		Serial.print("ms) ");
		if (ui16RetCodeValue == ui16CodeValue) {
			Serial.print("Tx: ");
			Serial.print(ui16Value);
			ui16RetCodeValue = (uint16_t)(ui16RetCodeValue * 2); // on realise un calcul simple pour certifier que le code recu est correct
			ui32SendValue = (uint32_t)(((uint32_t)ui16Value << 16) + (uint32_t)ui16RetCodeValue);
			Mirf.send((byte *)&ui32SendValue); // on envoie les 4 octets : [3:2]CAN, [1:0]CodeValeur)
			while (Mirf.isSending()); // on attend que le message soit envoye
			Serial.println(" OK");
		}
		else {
			Serial.println("Echec.");
		}
	}
}