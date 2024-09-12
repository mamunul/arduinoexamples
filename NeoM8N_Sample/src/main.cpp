#include <Arduino.h>
#include <HardwareSerial.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;
#define RXD2 16
#define TXD2 17

HardwareSerial neogps(1);

void setup()
{
  Serial.begin(115200);                             // Serial Monitor
  neogps.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop()
{
  while (neogps.available() > 0)
  {
    gps.encode(neogps.read());
    Serial.print("AVA=");
    Serial.print(neogps.available());
    Serial.print(" - ");
    Serial.print("LAT=");
    Serial.print(gps.location.lat(),6);
    Serial.print(" - ");
    Serial.print("LONG=");
    Serial.print(gps.location.lng(),6);
    Serial.print(" - ");
    Serial.print("ALT=");
    Serial.print(gps.altitude.meters(),6);
    Serial.print(" // ");
    Serial.println();
    delay(1000);
  }

  Serial.print("No Data available");
  Serial.println();
  delay(2000);
}