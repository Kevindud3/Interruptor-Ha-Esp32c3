#include "lux_sensor.h"
#include "mqtt_manager.h"
#include <BH1750.h>
#include <Wire.h>

BH1750 lightMeter;
const char* topic_lux = "interruptor/lux";
uint32_t lastLuxReading = 0;

void initLuxSensor() {
  Wire.begin(2, 1);
  lightMeter.begin();
}

void readAndPublishLux() {
  if (millis() - lastLuxReading > 2000) {
    lastLuxReading = millis();
    float lux = lightMeter.readLightLevel();
    char luxStr[8];
    dtostrf(lux, 1, 2, luxStr);
    client.publish(topic_lux, luxStr);
  }
}
