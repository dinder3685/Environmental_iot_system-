#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include "system_config.h" 
// Circular buffer for sensor data
typedef struct {
    float temperature[BUFFER_SIZE];
    float pressure[BUFFER_SIZE];
    float humidity[BUFFER_SIZE];
    int head;
    int count;
} CircularBuffer;


extern CircularBuffer sensorBuffer; 


void addToBuffer(float temp, float press, float hum) ;



#endif
