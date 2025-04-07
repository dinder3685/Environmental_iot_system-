#include "sensor_interface.h"
#include "sensor_config.h"  //
#include "system_config.h"  // 
#include <Arduino.h>
#include <Wire.h>
#include "bmp280config.h"



float i2c_sensor_read(uint8_t device_address, sensor_t sensor_type) {
    Wire.beginTransmission(device_address); 

    if (device_address == BME280_I2C_ADDR && sensor_type == SENSOR_HUMIDITY) {
        Wire.write(0xFD); // Register for humidity (BME280)
    } else if (device_address == HTU21_I2C_ADDR && sensor_type == SENSOR_TEMPERATURE) {
        Wire.write(0xE3); // Command for temperature (HTU21)
    }
    else if (device_address == BMP_I2C_ADDR && sensor_type == SENSOR_PRESSURE) {
        Wire.write(0xF7); // Command for pressure  (BMP280)
    }
    
     else {
        return -1; // Invalid input
    }

    Wire.endTransmission();
    delay(50);

    // Handle data differently based on the sensor
    if (device_address == BMP_I2C_ADDR && sensor_type == SENSOR_PRESSURE) {
        // BMP280: Read 3 bytes (MSB, LSB, XLSB)
        Wire.requestFrom(BMP_I2C_ADDR, 6); 
        if (Wire.available() < 6) {
            return -1; // Error in reading
        }

        uint8_t p_msb = Wire.read();
        uint8_t p_lsb = Wire.read();
        uint8_t p_xlsb = Wire.read();
        uint8_t t_msb = Wire.read();
        uint8_t t_lsb = Wire.read();
        uint8_t t_xlsb = Wire.read();

        int32_t rawPressure = ((int32_t)p_msb << 12) | ((int32_t)p_lsb << 4) | ((int32_t)p_xlsb >> 4);
        int32_t rawTemp = ((int32_t)t_msb << 12) | ((int32_t)t_lsb << 4) | ((int32_t)t_xlsb >> 4);


return compensateBMPPressure(rawPressure);
    }

    else if (device_address == BME280_I2C_ADDR && sensor_type == SENSOR_HUMIDITY) {
        // BME280: Read 2 bytes for humidity
        Wire.requestFrom(device_address, (uint8_t)2); 
        if (Wire.available() < 2) {
            return -1; // Error in reading
        }

        uint16_t rawData = (Wire.read() << 8) | Wire.read();
        return (rawData * 100.0) / 65536.0; // Convert to %RH
    }

    else if (device_address == HTU21_I2C_ADDR && sensor_type == SENSOR_TEMPERATURE) {
        // HTU21D: Read 2 bytes for temperature
        Wire.requestFrom(device_address, (uint8_t)2); 
        if (Wire.available() < 2) {
            return -1; // Error in reading
        }

        uint16_t rawData = (Wire.read() << 8) | Wire.read();
        return -46.85 + (175.72 * rawData) / 65536.0; // Convert to °C
    }

    return -1; // Invalid sensor
}



