#include "filtering.h"
#include "statistics.h"  // For movingMedianFilter
#include <cstring>
#include <cstdint>  // For int32_t, uint8_t, etc.
#include <Arduino.h>
float movingMedianFilter(float newValue, float* buffer, uint8_t windowSize, int* index) {
    buffer[(*index) % windowSize] = newValue;
    (*index)++;
    
    // Create a temporary array for sorting
    float temp[windowSize];
    memcpy(temp, buffer, sizeof(temp));
    
    // Simple bubble sort for the small window size
    for (int i = 0; i < windowSize - 1; i++) {
        for (int j = 0; j < windowSize - i - 1; j++) {
            if (temp[j] > temp[j + 1]) {
                float swap = temp[j];
                temp[j] = temp[j + 1];
                temp[j + 1] = swap;
            }
        }
    }
    
    // Return median
    return temp[windowSize / 2];
}
