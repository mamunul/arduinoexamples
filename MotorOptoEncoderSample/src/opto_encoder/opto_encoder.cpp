#include "opto_encoder.h"
#include "Arduino.h"
#include <avr/io.h>
#include "config.h"

static void (*on_motor1_each_pulse_local)(void);

void count_motor1_pulse()
{
    on_motor1_each_pulse_local();
}

void enable_tracker()
{
    attachInterrupt(digitalPinToInterrupt(ENCODER1_PIN), count_motor1_pulse, FALLING);
}

void setup_encoder(void (*on_motor1_each_pulse)(void))
{
    on_motor1_each_pulse_local = on_motor1_each_pulse;

    pinMode(ENCODER1_PIN, INPUT_PULLUP);
    enable_tracker();
}
