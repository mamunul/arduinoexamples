#include <Arduino.h>
#include <SPI.h>


#include <ADE7753.h>
const uint32_t CLK_FREQ = 3579545; // ADE7753 clock frequency in Hz
// ADE7753 meter; // Default constructor
// SPIClass Hspi(SPI);
ADE7753 meter(SPI, 15, 1000000); // Constructor for non-default SPI bus and frequency

void setup(){
  Serial.begin(115200);
  meter.begin();

  meter.setCh1Integrator(false);
  meter.setCh1Gain(ADE7753_GAIN_1);
  meter.setCh2Gain(ADE7753_GAIN_1);
  meter.setCh1FullScale(ADE7753_FS_0_5V);
  Serial.println("ADE7753 Initialized");
}

void loop(){
  uint32_t rmsVoltage = meter.readVoltageRMS();
  uint32_t rmsCurrent = meter.readCurrentRMS(); // 1865000
  rmsCurrent = meter.readCurrentRMS();

  Serial.print("Voltage RMS: ");
  Serial.print((rmsVoltage/3680.0));
  Serial.println(" V");

  Serial.print("Current RMS: ");
  Serial.print(rmsCurrent/62000.0);
  Serial.println(" A");

  double Frequency = (double)(CLK_FREQ / 8.0) / meter.readPeriod();
  Serial.print("Frequency: ");
  Serial.print(Frequency);
  Serial.println(" Hz");

  delay(1000); // 1 Hz read rate
}
