#ifndef Store
#define Store
#include <EEPROM.h>
#include <cstdlib>

typedef struct
{
  char* data;
  int byte_count;
} Char_Data;

typedef struct
{
  Char_Data port;
  Char_Data server;
  Char_Data client;
} MQTT_Params;

MQTT_Params read_params();
bool write(MQTT_Params params);

#endif