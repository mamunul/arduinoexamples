#ifndef pin_map
#define pin_map

#include <WString.h>

typedef struct
{
  String port;
  String server;
  String client;
} MQTT_Params;

#define WORK_FAN_BUTTON D1


#define CLIENT_COUNT 1
#define PARAMS_COUNT 3
#define BRAND String("xetoziot")
#define STORE
#define LOG
#define SERVER "assistant.local"
#define PORT "1883"
#define CLIENTID "loadshedding"
#endif