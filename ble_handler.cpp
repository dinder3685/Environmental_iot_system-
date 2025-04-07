#include "ble_handler.h"
#include "globals.h"
#include "system_config.h"


void MyServerCallbacks::onConnect(BLEServer* pServer) {
  deviceConnected = true;
  Serial.println("BLE Device Connected");
}

void MyServerCallbacks::onDisconnect(BLEServer* pServer) {
  deviceConnected = false;
  Serial.println("BLE Device Disconnected");
}

void initBLE() {
  BLEDevice::init("BME280-ESP32");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
  );

  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();
  pServer->getAdvertising()->start();
  Serial.println("Waiting for BLE client to connect...");
}


void handleBLEConnectionStatus() {
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // Give the bluetooth stack time to get ready
        pServer->startAdvertising();
        Serial.println("Restarting BLE advertising");
        oldDeviceConnected = deviceConnected;
    }
    if (deviceConnected && !oldDeviceConnected) {
        oldDeviceConnected = deviceConnected;
    }
}


void sendBLEStats(float tempMin, float tempMax, float tempMedian, float tempStdDev,
                 float pressMin, float pressMax, float pressMedian, float pressStdDev,
                 float humMin, float humMax, float humMedian, float humStdDev) {
    String statsData = "{";
    statsData += "\"temperature\":{";
    statsData += "\"min\":" + String(tempMin, 2) + ",";
    statsData += "\"max\":" + String(tempMax, 2) + ",";
    statsData += "\"median\":" + String(tempMedian, 2) + ",";
    statsData += "\"stddev\":" + String(tempStdDev, 2);
    statsData += "},";
    
    statsData += "\"pressure\":{";
    statsData += "\"min\":" + String(pressMin, 2) + ",";
    statsData += "\"max\":" + String(pressMax, 2) + ",";
    statsData += "\"median\":" + String(pressMedian, 2) + ",";
    statsData += "\"stddev\":" + String(pressStdDev, 2);
    statsData += "},";
    
    statsData += "\"humidity\":{";
    statsData += "\"min\":" + String(humMin, 2) + ",";
    statsData += "\"max\":" + String(humMax, 2) + ",";
    statsData += "\"median\":" + String(humMedian, 2) + ",";
    statsData += "\"stddev\":" + String(humStdDev, 2);
    statsData += "}";
    statsData += "}";
    
    if (deviceConnected) {
        pCharacteristic->setValue(statsData.c_str());
        pCharacteristic->notify();
        Serial.println("BLE Data Sent: " + statsData);
    } else {
        Serial.println("Stats calculated but no BLE connection: " + statsData);
    }
}