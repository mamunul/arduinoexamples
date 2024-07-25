#include "config.h"
#include <Arduino.h>

#define POWER_GONE_PIN D1

bool interrupt_occured = true;
int count = 0;

void ack()
{
  digitalWrite(D2, HIGH);
  delay(1);
  digitalWrite(D2, LOW);
}

void IRAM_ATTR power_gone()
{
  ack();
  count++;
  Serial.println(count);
}

void setup()
{
  delay(1000);
  Serial.begin(115200);
  Serial.println("Setup");
  pinMode(POWER_GONE_PIN, INPUT_PULLUP);
  pinMode(D2, OUTPUT);

  attachInterrupt(POWER_GONE_PIN, power_gone, FALLING);
}

void loop()
{
}
