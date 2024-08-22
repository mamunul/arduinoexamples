#include <Arduino.h>

// define things
static int32_t count_pressed = 0;
static const int32_t wait = 500;
// int btn = USER_BTN;
int led = LED_BUILTIN;
// int testpin1 = PC12;
// int testpin2 = PD2;

// Serial (Non USB)    RX    TX
// HardwareSerial Serial1(PA10, PA9);

void setup()
{ // put your setup code here, to run once:
  // int result = myFunction(2, 3);
  pinMode(led, OUTPUT);
  // pinMode(btn, INPUT);
  // pinMode(testpin1, OUTPUT);
  // pinMode(testpin2, OUTPUT);

  // begin hardware serial
  // Serial1.begin(9600);
}

// the loop function runs over and over again forever
void loop()
{
  // put your main code here, to run repeatedly:
  // Serial1.println();
  // Serial1.println("----------------------------------------");
  // Serial1.println("TEST");
  digitalWrite(led, HIGH);      // turn the LED on (HIGH is the voltage level)
  // digitalWrite(testpin1, HIGH); // turn the LED on (HIGH is the voltage level)
  // digitalWrite(testpin2, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(wait);
  digitalWrite(led, LOW);      // turn the LED off by making the voltage LOW
  // digitalWrite(testpin1, LOW); // turn the LED off by making the voltage LOW
  // digitalWrite(testpin2, LOW); // turn the LED off by making the voltage LOW
  delay(wait);
}