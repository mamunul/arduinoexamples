/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <Arduino.h>

#ifdef ESP8266DEVKIT
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

#ifndef STASSID
#define STASSID "Curiosity_IOT"
#define STAPSK "mamuniot"
#endif

const char *ssid = STASSID;
const char *password = STAPSK;

void setup()
{
  // enableWiFiAtBootTime();
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */

  WiFi.mode(WIFI_STA);
  // esp_wifi_set_max_tx_power(40);
  // WiFi.disconnect();
  // WiFi.enableInsecureWEP(true);
  // WiFi.disconnect();
  // WiFi.setTxPower(WIFI_POWER_19_5dBm);
  delay(100);

  WiFi.begin(ssid, password);
  // delay(100);
  // WiFi.printDiag(Serial);
  Serial.printf("Connection status: %d\n", WiFi.status());

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }else {
    Serial.println("WiFi not connected");
  }
  delay(5000);
}
