//As funções do radar são definidas nesse cabeçalho
#pragma once
#include "mqtt_manager.h"
#include "ld2410.h"
void initRadar();
void readAndPublishRadar();
