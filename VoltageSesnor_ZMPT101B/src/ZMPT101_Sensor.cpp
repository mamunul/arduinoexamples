#include "ZMPT101_Sensor.h"
#include <ZMPT101B.h>

#define ACTUAL_VOLTAGE 220.0f // Change this based on actual voltage

#define START_VALUE 0.0f
#define STOP_VALUE 1000.0f
#define STEP_VALUE 0.25f
#define TOLLERANCE 1.0f

#define MAX_TOLLERANCE_VOLTAGE (ACTUAL_VOLTAGE + TOLLERANCE)
#define MIN_TOLLERANCE_VOLTAGE (ACTUAL_VOLTAGE - TOLLERANCE)

#define SENSITIVITY 500.0f

ZMPT101B voltageSensor(0, 50); // Initialize with default pin and calibration value

void ZMPT101_Sensor::calibrate()
{
    float senstivityValue = START_VALUE;
    voltageSensor.setSensitivity(senstivityValue);
    float voltageNow = voltageSensor.getRmsVoltage();

    Serial.println("Start calculate");

    while (voltageNow > MAX_TOLLERANCE_VOLTAGE || voltageNow < MIN_TOLLERANCE_VOLTAGE)
    {
        if (senstivityValue < STOP_VALUE)
        {
            senstivityValue += STEP_VALUE;
            voltageSensor.setSensitivity(senstivityValue);
            voltageNow = voltageSensor.getRmsVoltage();
            Serial.print(senstivityValue);
            Serial.print(" => ");
            Serial.println(voltageNow);
        }
        else
        {
            Serial.println("Unfortunately the sensitivity value cannot be determined");
            return;
        }
    }
}

void ZMPT101_Sensor::setup(int pin)
{
    voltageSensor = ZMPT101B(pin, 50);
    voltageSensor.setSensitivity(SENSITIVITY);
}
float ZMPT101_Sensor::getVoltageRMS()
{
    return voltageSensor.getRmsVoltage();
}