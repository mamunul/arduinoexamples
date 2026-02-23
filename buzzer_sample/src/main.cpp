#include <Arduino.h>

// put function declarations here:
void single_buzz();
void notify_buzzer(bool is_on);

const int freq = 18000;    // Frequency in Hz
const int pwmChannel = 0; // PWM Channel (0-15)
const int resolution = 8;

void setup()
{

#if defined(ESP32) && defined(BUZZER_ENABLED)
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(BUZZER_PIN, pwmChannel);
#endif
}

void loop()
{
  // put your main code here, to run repeatedly:

  notify_buzzer(true);
  delay(2000);
  notify_buzzer(false);
  delay(2000);
}

// put function definitions here:
void single_buzz()
{
  int duration = 500; // Duration in milliseconds
#ifdef ESP32
  ledcWriteTone(pwmChannel, freq); // Set duty cycle to maximum (255 for 8-bit resolution)
  delay(duration);
  ledcWriteTone(pwmChannel, 0); // Turn off the buzzer
  delay(duration);
#else
  tone(BUZZER_PIN, freq, duration);
  delay(duration);
  noTone(BUZZER_PIN);
  delay(duration);
#endif
}

void notify_buzzer(bool is_on)
{
#if BUZZER_ENABLED
  if (is_on)
  {
    single_buzz();
  }
  else
  {
    single_buzz();
    single_buzz();
    single_buzz();
  }
#endif
}