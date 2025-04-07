#include <Wire.h>
#include <math.h> // For statistical calculations
#include "sensor_interface.h"
#include "globals.h"
#include "sensor_config.h"  //
#include "system_config.h" 
#include "bmp280config.h"
#include "circular_buffer.h"
#include "statistics.h"
#include "ble_handler.h"
#include "filtering.h"


void setup() {
   Serial.begin(115200);
    Wire.begin();

 // Initialize BMP280
    readBMPCalibrationData();
    startBMPMeasurement();
    initBLE();
}

void loop() { 
  
    
 void handleBLEConnectionStatus();
    // Take samples at 1Hz
    if (millis() - lastSampleTime >= SAMPLE_FREQ) {
        lastSampleTime = millis();
        
        // Read raw sensor values
        float temp =  i2c_sensor_read(HTU21_I2C_ADDR, SENSOR_TEMPERATURE);
        float press = i2c_sensor_read(BMP_I2C_ADDR, SENSOR_PRESSURE);
        float hum =i2c_sensor_read(BME280_I2C_ADDR, SENSOR_HUMIDITY);
        
        // Apply moving median filter
        temp = movingMedianFilter(temp, tempFilterBuffer, 5, &tempFilterIndex);
        press = movingMedianFilter(press, pressFilterBuffer, 5, &pressFilterIndex);
        hum = movingMedianFilter(hum, humFilterBuffer, 5, &humFilterIndex);
        // Add to circular buffer
        addToBuffer(temp, press, hum);
        
        Serial.print("Sample stored - Temp: ");
        Serial.print(temp);
        Serial.print("°C, Press: ");
        Serial.print(press);
        Serial.print("hPa, Hum: ");
        Serial.print(hum);
        Serial.println("%");
        
    }
    
    // Send BLE data every 30 seconds
    if (millis() - lastBleAdvTime >= BLE_ADV_INTERVAL) {
        lastBleAdvTime = millis();
        
        if (sensorBuffer.count > 0) {
            // Calculate statistics for each parameter
            float tempMin, tempMax, tempMedian, tempStdDev;
            float pressMin, pressMax, pressMedian, pressStdDev;
            float humMin, humMax, humMedian, humStdDev;
            
            calculateStats(sensorBuffer.temperature, sensorBuffer.count, 
                          &tempMin, &tempMax, &tempMedian, &tempStdDev);
            calculateStats(sensorBuffer.pressure, sensorBuffer.count, 
                          &pressMin, &pressMax, &pressMedian, &pressStdDev);
            calculateStats(sensorBuffer.humidity, sensorBuffer.count, 
                          &humMin, &humMax, &humMedian, &humStdDev);
            
           sendBLEStats(tempMin, tempMax, tempMedian, tempStdDev,
                        pressMin, pressMax, pressMedian, pressStdDev,
                        humMin, humMax, humMedian, humStdDev);
        }
    }
}



