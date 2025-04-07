#ifndef FILTERING_H
#define FILTERING_H
#include <cstring>
#include <cstdint>  // For int32_t, uint8_t, etc.
#include <Arduino.h>

float movingMedianFilter(float newValue, float* buffer, uint8_t windowSize, int* index);

#endif