/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <Arduino.h>
#include <vector>
#include <string>
#include <map>

#if defined(MEGA8)
#define LED_PIN PIN_PB0
#elif defined(ESP8266DEVKIT)
#define LED_PIN PIN_A0
#elif defined(ESP01)
#define LED_PIN PIN_PB0
#elif defined(ESP01s)
#define LED_PIN PIN_PB0
#elif defined(ESP32C3)
#define LED_PIN PIN_PB0
#elif defined(ESP32DEVKIT)
#define LED_PIN PIN_PB0
#elif defined(ESP32S3DEVKIT)
#define LED_PIN PIN_PB0
#elif defined(ESP32C6DEVKIT)
#define LED_PIN PIN_PB0
#elif defined(ESP32H2DEVKIT)
#define LED_PIN PIN_PB0
#endif

void
setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("setup");
}

void loop()
{
  Serial.println("loop1");
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
