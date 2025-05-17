//As funções do mqtt são definidas nesse cabeçalho
#pragma once
#include "PubSubClient.h"
#include "mqtt_callback.h"
#include "WiFi.h"

extern PubSubClient client;
void setupMQTT();
void mqttLoop();
