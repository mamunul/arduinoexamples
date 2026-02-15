#include <Arduino.h>
#include <SPI.h>
#include <ATM90E36.h>

#define CS_PIN 15
#define DEBUG_SERIAL
#define ESP8266

// SPIMODE must be zero
//  SPISettings settings(200000, MSBFIRST, SPI_MODE0);
// CommEnergyIC(WRITE, MMode0, 0x0087); // Mode Config (60 Hz, 3P4W)
// CommEnergyIC(WRITE, MMode1, 0x0000); // 0x5555 (x2) // 0x0000 (1x)
// function prototypes
void checkRegisters();

ATM90E36 meter(CS_PIN);

void setup()
{
  Serial.begin(115200);
  meter.begin();

  checkRegisters();
}

void checkRegisters()
{

  bool error = meter.calibrationError(); // Check for calibration errors
  if (error)
  {
    Serial.println("Calibration error detected!");
  }
  else
  {
    Serial.println("ATM90E36 Calibration OK.");
  }
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

  int checksum0 = meter.GetValueRegister(MMode0); // Example of reading a register value (GainA)
  Serial.println("MMode0:0x" + String(checksum0, HEX));
  delay(10);

  int checksum3 = meter.GetValueRegister(MMode1); // Example of reading a register value (GainA)
  Serial.println("MMode1:0x" + String(checksum3, HEX));
  delay(10);

  int adjStart = meter.GetValueRegister(AdjStart); // Example of reading a register value (GainA)
  Serial.println("AdjStart:0x" + String(adjStart, HEX));
  delay(10);

  int ugainA = meter.GetValueRegister(UgainA); // Example of reading a register value (GainA)
  Serial.println("UgainA:0x" + String(ugainA, HEX));
  delay(10);

  int uoffsetA = meter.GetValueRegister(UoffsetA); // Example of reading a register value (PoffsetA)
  Serial.println("UoffsetA:0x" + String(uoffsetA, HEX));
  delay(10);
}

void readValues()
{
  double voltageA = meter.GetLineVoltageA();
  double currentA = meter.GetLineCurrentA();
  double activePowerA = meter.GetActivePowerA();
  double reactivePowerA = meter.GetReactivePowerA();
  double apparentPowerA = meter.GetApparentPowerA();

  Serial.println("Voltage A: " + String(voltageA) + " V");
  Serial.println("Current A: " + String(currentA) + " A");
  Serial.println("Active Power A: " + String(activePowerA) + " W");
  Serial.println("Reactive Power A: " + String(reactivePowerA) + " VAR");
  Serial.println("Apparent Power A: " + String(apparentPowerA) + " VA");
  Serial.println();

}

void loop()
{

  readValues();
  delay(1500);
}
