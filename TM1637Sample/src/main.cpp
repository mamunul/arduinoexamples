#include <Arduino.h>
#include <string>
#include "ClockDisplay.h"

ClockDisplay display;
Time time2;
void setup()
{
  Serial.begin(115200);

  time2.hour = 11;
  time2.minute = 11;
  display.show(time2);
  Serial.println("setup");
}

void loop()
{
  time2.minute = time2.minute + 1;

  if (time2.minute >= 60)
    time2.hour = time2.hour + 1;
  time2.hour = time2.hour % 13;
  time2.minute = time2.minute % 60;
  display.show(time2);
  delay(500);
  Serial.println("loop");
}
