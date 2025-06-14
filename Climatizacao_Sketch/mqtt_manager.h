// As funções do mqtt são definidas nesse cabeçalho
#pragma once
#include "PubSubClient.h"
#include "WiFi.h"
#include "mqtt_callback.h"

extern PubSubClient client;
void setupMQTT();
void mqttLoop();
