// As funções callback são definidas nesse cabeçalho
#include "Arduino.h"
#include "mqtt_manager.h"

#pragma once

void callback(char *topic, byte *payload, unsigned int length);
