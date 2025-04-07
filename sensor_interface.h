#ifndef SENSOR_INTERFACE_H
#define SENSOR_INTERFACE_H

#include <stdint.h>

typedef enum {
    SENSOR_TEMPERATURE,
    SENSOR_HUMIDITY,
    SENSOR_PRESSURE 
} sensor_t;

float i2c_sensor_read(uint8_t device_address, sensor_t sensor_type) ;




#endif
