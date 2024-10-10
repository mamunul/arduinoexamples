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

#define PIN_COUNT 19

int pins[PIN_COUNT] = {2, 4, 5, 12, 13, 14, 15, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33};

void setup()
{
  Serial.begin(115200);
  // for (int i = 0; i < PIN_COUNT; i++)
  // {
  //   if (pins[i] == 15)
  //     continue;
  //   pinMode(pins[i], OUTPUT);
  // }
  pinMode(LED_PIN, OUTPUT);
  Serial.println("setup");
}

void loop()
{
  Serial.println("loop1");
  // for (int i = 0; i < PIN_COUNT; i++)
  // {
  //   if (pins[i] == 15)
  //     continue;
  //   digitalWrite(pins[i], HIGH);
  // }
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  // for (int i = 0; i < PIN_COUNT; i++)
  // {
  //   if (pins[i] == 15)
  //     continue;
  //   digitalWrite(pins[i], LOW);
  // }
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}
