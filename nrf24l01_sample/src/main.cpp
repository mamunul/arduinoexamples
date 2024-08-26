#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
// create an RF24 object
RF24 radio(D2, D1); // CE, CSN

// address through which two modules communicate.
const byte address[6] = "00001";
void transmitter_setup()
{
  radio.begin();

  // set the address
  radio.openWritingPipe(address);

  // Set module as transmitter
  radio.stopListening();
}

void transmitter_loop()
{
  // Send message to receiver
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));

  delay(1000);
}

void receiver_setup()
{
  // while (!Serial)
  //   ;
  Serial.begin(115200);

  radio.begin();

  // set the address
  radio.openReadingPipe(0, address);

  // Set module as receiver
  radio.startListening();
}

void receiver_loop()
{
  // Read the data if available in buffer
  if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}

void setup()
{
  // transmitter_setup();
  receiver_setup();
}

void loop()
{
  // transmitter_loop();
  receiver_loop();
}