#include "Arduino.h"
#include <avr/io.h>
#include "opto_encoder/opto_encoder.h"
#include "config.h"

int motor1_pulse_count = 0;

void on_motor1_encoder_pulse()
{
  motor1_pulse_count++;
}

void setup()
{
  int speed = 255;
  Serial.begin(9600);
  Serial.println("setup");
  setup_encoder(on_motor1_encoder_pulse);
}

void loop()
{
  Serial.print("motor1_pulse_count:");
  Serial.println(motor1_pulse_count);
}