#include <Arduino.h>

// define things
static int32_t count_pressed = 0;
static const int32_t wait = 1000;
// int btn = USER_BTN;
int led = LED_BUILTIN;

int pins[5] = {led, PA4, PA5, PA6, PA7};

void setup()
{
  for (int i = 0; i < 5; i++)
    pinMode(pins[i], OUTPUT);

  Serial.begin(115200);
}

// the loop function runs over and over again forever
void loop()
{
  for (int i = 0; i < 5; i++)
    digitalWrite(pins[i], HIGH); // turn the LED on (HIGH is the voltage level)
  delay(wait);
  for (int i = 0; i < 5; i++)
    digitalWrite(pins[i], LOW); // turn the LED off by making the voltage LOW
  delay(wait);
}