// AccessRF.h
#include <Arduino.h>
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>


// Prototypes
void RF_initSensorPart(void);
void RF_sendToMCU(uint16_t ui16CodeValue, uint16_t ui16Value);
