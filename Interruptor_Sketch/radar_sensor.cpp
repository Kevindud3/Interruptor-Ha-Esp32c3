// As leituras do radar são feitas aqui, se presença é detectada é publicado no
// tópico interruptor/radar O tempo entre as leituras pode ser ajustado na
// função readAndPublishRadar São feitas leituras da distancia e da energia do
// objeto rastreado, os valores são convertidos em strings e publicados em seus
// respectivos tópicos É feita a inicialização de um novo serial aqui para a
// comunicação com o microcontrolador do radar.
#include "radar_sensor.h"

#define MONITOR_SERIAL Serial
#define RADAR_SERIAL Serial1
#define RADAR_RX_PIN 20
#define RADAR_TX_PIN 21

ld2410 radar;
uint32_t lastReading = 0;
bool presenceState = false; // Flag to track the presence state

void initRadar() {
  RADAR_SERIAL.begin(256000, SERIAL_8N1, RADAR_RX_PIN, RADAR_TX_PIN);

  if (radar.begin(RADAR_SERIAL)) {
    MONITOR_SERIAL.println(F("OK"));
  } else {
    MONITOR_SERIAL.println(F("NÃO CONECTADO"));
  }
}

void readAndPublishRadar() {
  if (millis() - lastReading > 1000) { // Update frequency in milliseconds
    lastReading = millis();
    radar.read();

    bool presenceDetected = radar.presenceDetected();

    // If presence changes, publish accordingly
    if (presenceDetected && !presenceState) {
      client.publish("interruptor/radar", "Presença Detectada");
      presenceState = true; // Update the state to "presence detected"
    } else if (!presenceDetected && presenceState) {
      client.publish("interruptor/radar", "Presença Não Detectada");
      presenceState = false; // Update the state to "no presence"
    }

    if (presenceDetected) {
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
    }
  }
}
