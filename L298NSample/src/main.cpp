#include "Arduino.h"
#include <avr/io.h>

#include "config.h"
#include "motor_driver/l298.h"
int speed = 100;
void setup()
{

  Serial.begin(9600);
  Serial.println("setup");

  setup_l298();
  setMotor1Rotation(ROTATION_CW);
  setMotor2Rotation(ROTATION_CCW);
  runMotor1(speed);
  runMotor2(speed);
}

void loop()
{

  Serial.println(speed);
  runMotor1(speed);
  runMotor2(speed);
  speed += 10;

  speed %= 255;
  delay(5000);
}