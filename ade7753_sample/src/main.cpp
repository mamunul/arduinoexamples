#include <Arduino.h>
#include <SPI.h>

#include <ADE7753.h>
const uint32_t CLK_FREQ = 3579545; // ADE7753 clock frequency in Hz
// ADE7753 meter; // Default constructor
// SPIClass Hspi(SPI);
ADE7753 meter(SPI, 15, 1000000); // Constructor for non-default SPI bus and frequency
uint32_t last_active_power = 0;
uint32_t last_apparent_power = 0;
void setup()
{
  Serial.begin(115200);
  meter.begin();

  // meter.setCh1Integrator(false);
  meter.setCh1Gain(ADE7753_GAIN_1);
  meter.setCh2Gain(ADE7753_GAIN_1);
  meter.setCh1FullScale(ADE7753_FS_0_5V);
  Serial.println("ADE7753 Initialized");
  // meter.reset();
}

void loop()
{
  uint32_t rmsVoltage = meter.readVoltageRMS();
  uint32_t rmsCurrent = meter.readCurrentRMS(); // 1865000
  uint32_t active_power = meter.readAEnergy();
  uint32_t apparent_power = meter.readVAEnergy();

  uint16_t status = meter.status() ; // Clear any pending interrupts
  Serial.print("Status in binary: 0b");
  Serial.println(status,BIN);

  Serial.print("7th bit: ");
  Serial.println((status & (1<<7)) ? "1" : "0");


  Serial.print("Raw Voltage RMS: ");
  Serial.print(rmsVoltage);
  Serial.println(" (3680 = 1 V)");

  Serial.print("Voltage RMS: ");
  Serial.print((rmsVoltage / 3680.0));
  Serial.println(" V");

  Serial.print("Raw Current RMS: ");
  Serial.print(rmsCurrent);
  Serial.println(" (62000 = 1 A)");

  Serial.print("Current RMS: ");
  Serial.print(rmsCurrent / 62000.0);
  Serial.println(" A");

  // Serial.print("Accumulated Active Energy: ");
  // Serial.print(active_power);
  // Serial.println(" VA");
  // Serial.print("Active Energy Change: ");
  // Serial.print(active_power - last_active_power);
  // Serial.println(" VA");
  // last_active_power = active_power;

  // Serial.print("Accumulated Apparent Energy: ");
  // Serial.print(apparent_power);
  // Serial.println(" VAr");
  // Serial.print("Apparent Energy Change: ");
  // Serial.print(apparent_power - last_apparent_power);
  // Serial.println(" VAr");
  // last_apparent_power = apparent_power;

  double Frequency = (double)(CLK_FREQ / 8.0) / meter.readPeriod();
  Serial.print("Frequency: ");
  Serial.print(Frequency);
  Serial.println(" Hz");

  delay(1500); // 1 Hz read rate
}
