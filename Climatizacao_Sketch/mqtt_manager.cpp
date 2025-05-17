//A conexão com o cliente MQTT é feita aqui, a inscrição de tópicos de leitura é feita aqui.
#include "mqtt_manager.h"

const char* mqtt_server = "192.168.88.253";
const char* mqtt_user = "mosquito";
const char* mqtt_password = "12345";

WiFiClient espClient;
PubSubClient client(espClient);

void setupMQTT() {
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Conectando ao MQTT...");
    if (client.connect("ESP32Client2", mqtt_user, mqtt_password)) {
      Serial.println("Conectado ao MQTT");
      client.subscribe("climatização/rele");

    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void mqttLoop() {
  client.loop();
}
