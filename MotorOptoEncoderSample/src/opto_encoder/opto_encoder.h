#ifndef OPTO_ENCODER
#define OPTO_ENCODER

#define PULSES_PER_TURN 20

void setup_encoder(void (*on_motor1_each_pulse)(void));
#endif