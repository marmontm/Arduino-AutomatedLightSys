// AccessRF.h
#include <Arduino.h>
#include "BaseArduino.h"
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

//#include <SPI\\SPI.h>
//#include <Mirf\\Mirf.h>
//#include <Mirf\\nRF24L01.h>
//#include <Mirf\\MirfHardwareSpiDriver.h>

// Prototypes
void RF_initOperativePart(void);
uint16_t RF_requestSensor(uint16_t ui16CodeValue, uint16_t ui16RetValue_old);
