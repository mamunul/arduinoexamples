#include <Arduino.h>
#include <Servo.h>

Servo esc;
#define ESC_PIN D4
int dutyCycle = 30;
int freq = 500;
void setup()
{

  Serial.begin(115200);
  Serial.println("setup complete");
  analogWriteFreq(freq);
}

void loop()
{
  for (dutyCycle = 10; dutyCycle < 40; dutyCycle += 5)
  {
    Serial.print("freq: ");
    Serial.print(freq);
    Serial.print(" dutyCycle: ");
    Serial.println(dutyCycle);
    analogWrite(ESC_PIN, dutyCycle);
    delay(5000);
  }
}
