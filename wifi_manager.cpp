#include "wifi_manager.h"
#include <WiFi.h>

const char* ssid = "HA AP";
const char* password = "12345678";

void connectToWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao Wi-Fi...");
  }
  Serial.println("Conectado ao Wi-Fi");
}
