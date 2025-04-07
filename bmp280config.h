#ifndef BMP280CONFIG_H
#define BMP280CONFIG_H
#include <cstdint>  // For int32_t, uint8_t, etc.

void readBMPCalibrationData();
void startBMPMeasurement();

float compensateBMPPressure(int32_t rawPressure);

#endif
