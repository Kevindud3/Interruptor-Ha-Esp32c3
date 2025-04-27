//As funções callback são definidas nesse cabeçalho
#include "esp32-hal-ledc.h"
#include "mqtt_manager.h"
#include "Arduino.h"
#include "sleep.h"

#pragma once


void callback(char* topic, byte* payload, unsigned int length);
void setupPWM();
