// As funções do sensor de temperatura são definidas nesse cabeçalho
#pragma once
#include "Adafruit_AHT10.h"
#include "mqtt_manager.h"

void init_Temp();
void readAndPublishTemp();
