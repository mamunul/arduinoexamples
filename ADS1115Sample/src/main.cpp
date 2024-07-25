#include <Arduino.h>
#include <string>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>

Adafruit_ADS1115 ads;
void setup()
{
  Serial.begin(115200);

  if (!ads.begin())
  {
    Serial.println("Failed to initialize ADS.");
  }
  else
  {
    ads.setDataRate(RATE_ADS1115_860SPS);
    Serial.println("Success to initialize ADS.");
  }
}

void loop()
{

  int16_t adc_value = ads.readADC_SingleEnded(1);
  Serial.print("adc:");
  Serial.println(adc_value);
  float v = ads.computeVolts(adc_value);
  Serial.print("v:");
  Serial.println(v * 2);
  delay(500);
}
