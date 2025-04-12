//As funções do mqtt são definidas nesse cabeçalho
#pragma once
#include <PubSubClient.h>

extern PubSubClient client;
void setupMQTT();
void mqttLoop();
