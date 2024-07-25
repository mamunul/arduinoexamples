#include "ClockDisplay.h"

#include <Arduino.h>
#include <TM1637Display.h>

#include "config.h"

TM1637Display clockDisplay = TM1637Display(CLK_PIN, DATA_PIN);

void ClockDisplay::show(Time time)
{
    clockDisplay.setBrightness(5);

    unsigned long time_seconds = time.hour * 100 + time.minute;
    clockDisplay.showNumberDecEx(time_seconds, 0b01000000, true, 4, 0);
}