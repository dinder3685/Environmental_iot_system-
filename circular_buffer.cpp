#include "circular_buffer.h"
#include "system_config.h" 


 CircularBuffer sensorBuffer = {0};

void addToBuffer(float temp, float press, float hum) {
    if (sensorBuffer.count < BUFFER_SIZE) {
        sensorBuffer.count++;
    }
    
    sensorBuffer.temperature[sensorBuffer.head] = temp;
    sensorBuffer.pressure[sensorBuffer.head] = press;
    sensorBuffer.humidity[sensorBuffer.head] = hum;
    
    sensorBuffer.head = (sensorBuffer.head + 1) % BUFFER_SIZE;
}