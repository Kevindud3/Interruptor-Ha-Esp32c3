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
  MONITOR_SERIAL.print(F("\nConnect LD2410 radar TX to GPIO:"));
  MONITOR_SERIAL.println(RADAR_RX_PIN);
  MONITOR_SERIAL.print(F("LD2410 radar sensor initialising: "));

  RADAR_SERIAL.begin(256000, SERIAL_8N1, RADAR_RX_PIN, RADAR_TX_PIN);

  if (radar.begin(RADAR_SERIAL)) {
    MONITOR_SERIAL.println(F("OK"));
  } else {
    MONITOR_SERIAL.println(F("not connected"));
  }
}

void readAndPublishRadar() {
  if (millis() - lastReading > 1000) {
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
