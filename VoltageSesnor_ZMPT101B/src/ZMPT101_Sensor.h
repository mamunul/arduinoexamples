#ifndef ZMPT101_SENSOR_H
#define ZMPT101_SENSOR_H
#include <Arduino.h>

class ZMPT101_Sensor
{
public:
    void setup(int pin);
    // void begin(int pin, float calibrationFactor);
    void calibrate();
    float getVoltageRMS();
};

#endif // ZMPT101_SENSOR_H