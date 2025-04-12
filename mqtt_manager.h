#pragma once
#include <PubSubClient.h>

extern PubSubClient client;
void setupMQTT();
void mqttLoop();
