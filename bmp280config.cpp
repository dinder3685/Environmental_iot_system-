#include "bmp280config.h"
#include "globals.h"
#include <Wire.h>
#include "sensor_config.h"  //
#include "system_config.h"  // 
#include <cstdint>  // For int32_t, uint8_t, etc.

void startBMPMeasurement() {
    Wire.beginTransmission(BMP_I2C_ADDR);
    Wire.write(0xF4);  // Control register
    Wire.write(0x27);  // Normal mode, oversampling = 1
    Wire.endTransmission();
}


void readBMPCalibrationData() {
    Wire.beginTransmission(BMP_I2C_ADDR);
    Wire.write(0x88);  // Start at first calibration register
    Wire.endTransmission();
    Wire.requestFrom(BMP_I2C_ADDR, 24);  // Read 24 bytes

    dig_T1 = Wire.read() | (Wire.read() << 8);
    dig_T2 = Wire.read() | (Wire.read() << 8);
    dig_T3 = Wire.read() | (Wire.read() << 8);
    dig_P1 = Wire.read() | (Wire.read() << 8);
    dig_P2 = Wire.read() | (Wire.read() << 8);
    dig_P3 = Wire.read() | (Wire.read() << 8);
    dig_P4 = Wire.read() | (Wire.read() << 8);
    dig_P5 = Wire.read() | (Wire.read() << 8);
    dig_P6 = Wire.read() | (Wire.read() << 8);
    dig_P7 = Wire.read() | (Wire.read() << 8);
    dig_P8 = Wire.read() | (Wire.read() << 8);
    dig_P9 = Wire.read() | (Wire.read() << 8);
}



float compensateBMPPressure(int32_t rawPressure) {
    int64_t var1, var2, p;
    var1 = ((int64_t)t_fine) - 128000;
    var2 = var1 * var1 * (int64_t)dig_P6;
    var2 = var2 + ((var1 * (int64_t)dig_P5) << 17);
    var2 = var2 + (((int64_t)dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)dig_P3) >> 8) + ((var1 * (int64_t)dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1)) * ((int64_t)dig_P1) >> 33;

    if (var1 == 0) return 0;  // Prevent division by zero
    p = 1048576 - rawPressure;
    p = (((p << 31) - var2) * 3125) / var1;
    var1 = (((int64_t)dig_P9) * (p >> 13) * (p >> 13)) >> 25;
    var2 = (((int64_t)dig_P8) * p) >> 19;
    p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7) << 4);
    return (float)p /(100 * 256.0);  // Convert to hPa
}



