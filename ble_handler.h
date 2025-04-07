#ifndef BLE_HANDLER_H
#define BLE_HANDLER_H
#include "globals.h"
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "system_config.h"




void sendBLEStats(float tempMin, float tempMax, float tempMedian, float tempStdDev,
                 float pressMin, float pressMax, float pressMedian, float pressStdDev,
                 float humMin, float humMax, float humMedian, float humStdDev);
void initBLE();
void handleBLEConnectionStatus();

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) override;
  void onDisconnect(BLEServer* pServer) override;
};

#endif
