#include "radar_sensor.h"
#include "mqtt_manager.h"
#include <ld2410.h>

#define MONITOR_SERIAL Serial
#define RADAR_SERIAL Serial1
#define RADAR_RX_PIN 20
#define RADAR_TX_PIN 21

ld2410 radar;
uint32_t lastReading = 0;

void initRadar() {
  RADAR_SERIAL.begin(256000, SERIAL_8N1, RADAR_RX_PIN, RADAR_TX_PIN);

  if (radar.begin(RADAR_SERIAL)) {
    MONITOR_SERIAL.println(F("OK"));
  } else {
    MONITOR_SERIAL.println(F("not connected"));
  }
}

void readAndPublishRadar() {
  if (millis() - lastReading > 30000) { //Quão frequentemente o valores do radar são atualizados em milésimos de segundo
    lastReading = millis();
    radar.read();

    if (radar.presenceDetected()) {
      client.publish("interruptor/radar", "Presenca Detectada");

      if (radar.stationaryTargetDetected()) {
        char distStr[8], energyStr[8];
        itoa(radar.stationaryTargetDistance(), distStr, 10);
        itoa(radar.stationaryTargetEnergy(), energyStr, 10);
        client.publish("interruptor/radar/estacionario/distancia", distStr);
        client.publish("interruptor/radar/estacionario/energia", energyStr);
      }

      if (radar.movingTargetDetected()) {
        char distStr[8], energyStr[8];
        itoa(radar.movingTargetDistance(), distStr, 10);
        itoa(radar.movingTargetEnergy(), energyStr, 10);
        client.publish("interruptor/radar/movendo/distancia", distStr);
        client.publish("interruptor/radar/movendo/energia", energyStr);
      }
    } else {
      client.publish("interruptor/radar", "Presenca Não Detectada");
    }
  }
}
