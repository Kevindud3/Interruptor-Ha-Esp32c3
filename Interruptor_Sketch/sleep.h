//As funções do radar são definidas nesse cabeçalho
#pragma once
#include "esp_sleep.h"
#include "Arduino.h"
#include "PubSubClient.h"
#include "mqtt_manager.h"
void goToDeepSleep(int wakeUpPin1);
