//Arquivo main do Arduino onde todas as funções são chamadas e o serial é iniciado
#include "wifi_manager.h"
#include "mqtt_manager.h"
#include "radar_sensor.h"
#include "lux_sensor.h"

const int pinoRELE = 0;

void setup() {
  pinMode(pinoRELE, OUTPUT);
  Serial.begin(115200);
  connectToWiFi();
  setupMQTT();
  setupPWM();
  initLuxSensor();
  initRadar();
}

void loop() {
  mqttLoop();
  readAndPublishLux();
  readAndPublishRadar();
}
