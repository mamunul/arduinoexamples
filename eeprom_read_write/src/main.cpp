/*
   EEPROM Write

   Stores values read from analog input 0 into the EEPROM.
   These values will stay in the EEPROM when the board is
   turned off and may be retrieved later by another sketch.
*/
#include <Arduino.h>
#include <EEPROM.h>
#include <string.h>
#include "Store.h"
MQTT_Params params2; 
// the current address in the EEPROM (i.e. which byte
// we're going to write to next)

void setup() {
  Serial.begin(115200);
  MQTT_Params params;
  char *server = (char *)"assistant.local";
  char *port = (char *)"4578";
  char *client = (char *)"worklight";

  Char_Data port_data;
  port_data.data = port;
  port_data.byte_count = strlen(port);

  params.port = port_data;

  Char_Data server_data;
  server_data.data = server;
  server_data.byte_count = strlen(server);

  params.server = server_data;

  Char_Data client_data;
  client_data.data = client;
  client_data.byte_count = strlen(client);

  params.client = client_data;

  write(params);

  params2 = read_params();
  params2.client.data[params2.client.byte_count] = '\0';

}

void loop() {
  Serial.println("------------------");
  Serial.println(params2.server.data);
  Serial.println(params2.port.data);
  Serial.println(params2.client.data);
  delay(3000);
}
