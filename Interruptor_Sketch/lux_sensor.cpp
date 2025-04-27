//A leitura do sensor de lux é feita aqui, a função initLuxSensor inicia o sensor e indica os pinos de comunicação
//A função lightMeter.begin inicia a leitura do sensor
//A função readAndPublishLux checa se a última leitura foi a mais de 5 segundos atrás
//A leitura é feita com a função readLightLevel e esse valor é convertido em uma string e postado no tópico interruptor/lux
#include "lux_sensor.h"

BH1750 lightMeter;
const char* topic_lux = "interruptor/lux";
uint32_t lastLuxReading = 0;

void initLuxSensor() {
  Wire.begin(2, 1); //Pinos de comunicação SLA e SDA
  lightMeter.begin();
}

void readAndPublishLux() {
  if (millis() - lastLuxReading > 5000) { //Quão frequentemente o valor de lux é atualizado em milésimos de segundo
    lastLuxReading = millis();
    float lux = lightMeter.readLightLevel();
    char luxStr[8];
    dtostrf(lux, 1, 2, luxStr);
    client.publish(topic_lux, luxStr);
  }
}
