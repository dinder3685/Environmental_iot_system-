#ifndef GLOBALS_H
#define GLOBALS_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// BLE objects
extern BLEServer* pServer;
extern BLECharacteristic* pCharacteristic;
extern bool deviceConnected;
extern bool oldDeviceConnected;

// Calibration values
extern uint16_t dig_T1;
extern int16_t dig_T2, dig_T3;
extern uint16_t dig_P1;
extern int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
extern int32_t t_fine;




// tuming 
extern unsigned long lastSampleTime;
extern unsigned long lastBleAdvTime;


// the used buffer
extern float tempFilterBuffer[5];
extern float pressFilterBuffer[5];
extern float humFilterBuffer[5];

//
extern int tempFilterIndex;
extern int pressFilterIndex;
extern int humFilterIndex;

#endif
