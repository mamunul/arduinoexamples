#include <Arduino.h>
#include <SPI.h>
#include <ATM90E36.h>

#define CS_PIN 10

ATM90E36 meter(CS_PIN);

void setup()
{
  Serial.begin(115200);
  meter.begin();

  meter.calibrationError(); // Check for calibration errors
  Serial.println("ATM90E36 Sample");
}

void loop()
{
  /*Repeatedly fetch some values from the ATM90E36 */
  int sys0 = meter.GetSysStatus0();
  int sys1 = meter.GetSysStatus1();
  int en0 = meter.GetMeterStatus0();
  int en1 = meter.GetMeterStatus1();
  Serial.println("S0:0x" + String(sys0, HEX));
  delay(10);
  Serial.println("S1:0x" + String(sys1, HEX));
  delay(10);
  Serial.println("E0:0x" + String(en0, HEX));
  delay(10);
  Serial.println("E1:0x" + String(en1, HEX));
  double voltageA = meter.GetLineVoltageA();
  delay(10);
  double currentA = meter.GetLineCurrentA();
  Serial.println("IA:" + String(currentA) + "A");
  delay(10);
  double freq = meter.GetFrequency();
  delay(10);
  Serial.println("f" + String(freq) + "Hz");
  double reactive_power = meter.GetReactivePowerA();
  delay(10);
  Serial.println("Reactive Power:" + String(reactive_power) + "VAR");
  delay(10);
  double apparent_power = meter.GetApparentPowerA();
  delay(10);
  Serial.println("Apparent Power:" + String(apparent_power) + "VA");
  delay(10);

  double power = meter.GetActivePowerA();
  delay(10);
  Serial.println("Active Power:" + String(power) + "W");
  delay(10);
  double pf = meter.GetPowerFactorA();
  delay(10);
  Serial.println("Power Factor:" + String(pf));
  delay(1000);
}
