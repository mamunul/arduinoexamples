#ifndef L298
#define L298
#include "Arduino.h"
#include <avr/io.h>
#include "config.h"

#define ROTATION_CW 1
#define ROTATION_CCW 2
#define ROTATION_OFF 3

void setup_l298();
void runMotor1(int speed);
void runMotor2(int speed);
void setMotor1Rotation(int rotation);
void setMotor2Rotation(int rotation);

#endif