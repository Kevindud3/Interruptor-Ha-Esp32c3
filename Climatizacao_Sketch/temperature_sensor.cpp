// As medições de temperatura e humidade são feitas aqui a publicação para o HA
// também é feita aqui.
#include "temperature_sensor.h"

Adafruit_AHT10 aht;

void init_Temp() {

  if (!aht.begin()) {
    Serial.println("Could not find AHT10? Check wiring");
    while (1)
      delay(10);
  }
  Serial.println("AHT10 found");
}

void readAndPublishTemp() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  char tempStr[8], humiStr[8];
  dtostrf(temp.temperature, 1, 2, tempStr);
  dtostrf(humidity.relative_humidity, 1, 2, humiStr);
  client.publish("sensor/humi", humiStr);
  client.publish("sensor/temp", tempStr);

  delay(500);
}
