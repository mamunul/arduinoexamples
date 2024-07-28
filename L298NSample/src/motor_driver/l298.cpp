#include "l298.h"

void setup_l298()
{
    // Set all the motor control pins to outputs
    pinMode(MOTOR1_PWM, OUTPUT);
    pinMode(MOTOR2_PWM, OUTPUT);
    pinMode(MOTOR1_IN1, OUTPUT);
    pinMode(MOTOR1_IN2, OUTPUT);
    pinMode(MOTOR2_IN3, OUTPUT);
    pinMode(MOTOR2_IN4, OUTPUT);

    // Turn off motors - Initial state
    digitalWrite(MOTOR1_IN1, LOW);
    digitalWrite(MOTOR1_IN2, LOW);
    digitalWrite(MOTOR2_IN3, LOW);
    digitalWrite(MOTOR2_IN4, LOW);
}

void runMotor1(int speed)
{
    analogWrite(MOTOR1_PWM, speed);
}

void runMotor2(int speed)
{
    analogWrite(MOTOR2_PWM, speed);
}

void setMotor1Rotation(int rotation)
{
    if (rotation == ROTATION_CW)
    {
        digitalWrite(MOTOR1_IN1, HIGH);
        digitalWrite(MOTOR1_IN2, LOW);
    }
    else if (rotation == ROTATION_CCW)
    {
        digitalWrite(MOTOR1_IN1, LOW);
        digitalWrite(MOTOR1_IN2, HIGH);
    }
    else if (rotation == ROTATION_OFF)
    {
        digitalWrite(MOTOR1_IN1, LOW);
        digitalWrite(MOTOR1_IN2, LOW);
    }
}

void setMotor2Rotation(int rotation)
{
    if (rotation == ROTATION_CW)
    {
        digitalWrite(MOTOR2_IN3, HIGH);
        digitalWrite(MOTOR2_IN4, LOW);
    }
    else if (rotation == ROTATION_CCW)
    {
        digitalWrite(MOTOR2_IN3, LOW);
        digitalWrite(MOTOR2_IN4, HIGH);
    }
    else if (rotation == ROTATION_OFF)
    {
        digitalWrite(MOTOR2_IN3, LOW);
        digitalWrite(MOTOR2_IN4, LOW);
    }
}