#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include "config.h"

double REFERENCE_RESISTANCE = 100000;
double NOMINAL_RESISTANCE = 100000;
double NOMINAL_TEMPERATURE = 298.15; // 25;
double B_VALUE = 3950;
double ADS1115_ADC_RESOLUTION = 65535;

Adafruit_ADS1115 ads;

double get_NTC_ADC()
{
  int16_t adc_value = ads.readADC_SingleEnded(1);
  return double(adc_value);
}

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
  double adc = ads.readADC_SingleEnded(1);
  Serial.print("adc: ");
  Serial.println(adc);

  double volt = ads.computeVolts(adc);
  Serial.print("volt: ");
  Serial.println(volt);

  double Vcc = 3.3;
  double Rth = (volt * REFERENCE_RESISTANCE) / (Vcc - volt);

  Serial.print("Rth: ");
  Serial.println(Rth);

  const float roomTemp = 298.15; // room temperature in Kelvin
  float tKelvin = (B_VALUE * roomTemp) /
                  (B_VALUE + (roomTemp * log(Rth / NOMINAL_RESISTANCE)));
  float tCelsius = tKelvin - 273.15;
  float tFahrenheit = (tCelsius * 9.0) / 5.0 + 32.0;

  Serial.print("Temperature: ");
  Serial.print(tFahrenheit);
  Serial.print(" F; ");
  Serial.print(tCelsius);
  Serial.println(" C");

  delay(5000);
}
