// As funções do radar são definidas nesse cabeçalho
#pragma once
#include "Arduino.h"
#include "PubSubClient.h"
#include "esp_sleep.h"
#include "mqtt_manager.h"
void goToDeepSleep(int wakeUpPin1);
