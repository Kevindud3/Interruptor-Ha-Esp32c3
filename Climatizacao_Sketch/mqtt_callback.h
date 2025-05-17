//As funções callback são definidas nesse cabeçalho
#include "mqtt_manager.h"
#include "Arduino.h"

#pragma once


void callback(char* topic, byte* payload, unsigned int length);
