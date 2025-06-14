// As funções do sensor de lux são declaradas nesse cabeçalho
#pragma once
#include "BH1750.h"
#include "Wire.h"
#include "mqtt_manager.h"
void initLuxSensor();
void readAndPublishLux();
