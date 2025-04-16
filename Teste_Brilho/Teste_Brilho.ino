//Arquivo main do Arduino onde todas as funções são chamadas e o serial é iniciado
#include "wifi_manager.h"
#include "mqtt_callback.h"
#include "mqtt_manager.h"

void setup() {
  Serial.begin(115200);
  connectToWiFi();
  setupPWM();
  setupMQTT();
}

void loop() {
  mqttLoop();
}
