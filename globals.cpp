#include "globals.h"

// BLE Setup
BLEServer* pServer = nullptr;
BLECharacteristic* pCharacteristic = nullptr;
bool deviceConnected = false;
bool oldDeviceConnected = false;

uint16_t dig_T1;
int16_t dig_T2, dig_T3;
uint16_t dig_P1;
int16_t dig_P2, dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9;
int32_t t_fine;




unsigned long lastSampleTime = 0;
unsigned long lastBleAdvTime = 0;
float tempFilterBuffer[5] = {0};
float pressFilterBuffer[5] = {0};
float humFilterBuffer[5] = {0};
int tempFilterIndex = 0;
int pressFilterIndex = 0;
int humFilterIndex = 0;