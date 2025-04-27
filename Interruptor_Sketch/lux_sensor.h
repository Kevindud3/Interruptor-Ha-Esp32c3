//As funções do sensor de lux são declaradas nesse cabeçalho
#pragma once
#include "mqtt_manager.h"
#include "BH1750.h"
#include "Wire.h"
void initLuxSensor();
void readAndPublishLux();
