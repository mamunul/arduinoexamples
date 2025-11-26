#include <Arduino.h>
#include <ZMPT101_Sensor.h>

// put function declarations here:

ZMPT101_Sensor sensor;

void setup()
{
  Serial.begin(115200);
  sensor.setup(D1);
  sensor.calibrate();
  Serial.println("Setup complete");
}

void loop()
{

  float voltage = sensor.getVoltageRMS();

  Serial.print("Voltage RMS: ");
  Serial.print(voltage);
  Serial.println(" V");
  delay(1000);
}