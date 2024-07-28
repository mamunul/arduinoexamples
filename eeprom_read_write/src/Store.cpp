#include "Store.h"


bool write(Char_Data data, int addr) {
  EEPROM.write(addr++, data.byte_count);
  int i = 0;
  while (i < data.byte_count) {
    EEPROM.write(addr++, data.data[i++]);
  }
  return true;
}

Char_Data read_data(int addr) {
  Char_Data data;
  data.byte_count = EEPROM.read(addr++);
  int i = 0;
  data.data = (char *)malloc(data.byte_count);
  while (i < data.byte_count) {
    data.data[i++] = EEPROM.read(addr++);
  }
  return data;
}

bool write(MQTT_Params params) {
  EEPROM.begin(512);

  write(params.port, 0);
  int addr = params.port.byte_count + 1;
  write(params.server, addr);
  addr = params.server.byte_count + params.port.byte_count + 2;
  write(params.client, addr);
  return EEPROM.commit();
}

MQTT_Params read_params() {
  EEPROM.begin(512);
  MQTT_Params params;

  params.port = read_data(0);
  int addr = params.port.byte_count + 1;
  params.server = read_data(addr);
  addr = params.server.byte_count + params.port.byte_count + 2;
  params.client = read_data(addr);

  return params;
}