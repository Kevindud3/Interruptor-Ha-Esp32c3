//A conexão com o cliente MQTT é feita aqui, a inscrição de tópicos de leitura é feita aqui.
#include "mqtt_manager.h"
#include "mqtt_callback.h"
#include <WiFi.h>

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
    if (client.connect("ESP32Client1", mqtt_user, mqtt_password)) { //trocar o nome do cliente caso haja mais de 1 esp
      Serial.println("Conectado ao MQTT");
      client.subscribe("lampada/brilho");
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
