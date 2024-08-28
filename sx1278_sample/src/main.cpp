#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

// define the pins used by the transceiver module
#define NSS D2
#define RST D4
#define DIO0 D1

int counter = 0;

void transmitter_setup()
{
  Serial.println("LoRa Sender");

  // setup LoRa transceiver module
  LoRa.setPins(NSS, RST, DIO0);

  // replace the LoRa.begin(---E-) argument with your location's frequency
  // 433E6 for Asia
  // 868E6 for Europe
  // 915E6 for North America
  while (!LoRa.begin(433E6))
  {
    Serial.println(".");
    delay(500);
  }
  // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void transmitter_loop()
{
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(10000);
}

void receiver_setup()
{
  // initialize Serial Monitor

  Serial.println("LoRa Receiver");

  // setup LoRa transceiver module
  LoRa.setPins(NSS, RST, DIO0);

  // replace the LoRa.begin(---E-) argument with your location's frequency
  // 433E6 for Asia
  // 868E6 for Europe
  // 915E6 for North America
  while (!LoRa.begin(433E6))
  {
    Serial.println(".");
    delay(500);
  }
  // Change sync word (0xF3) to match the receiver
  // The sync word assures you don't get LoRa messages from other LoRa transceivers
  // ranges from 0-0xFF
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void receiver_loop()
{
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available())
    {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData);
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}

void setup()
{

  Serial.begin(115200);
  // transmitter_setup();
  receiver_setup();
}

void loop()
{
  // transmitter_loop();
  receiver_loop();
}
