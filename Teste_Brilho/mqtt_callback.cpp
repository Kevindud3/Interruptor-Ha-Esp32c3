//Mensagens do MQTT são recebidas aqui, nossas mensagens são de texto simples a função callback aqui lé a mensagem
//e a reescreve na variável message que é uma string. E a imprime para debug.
#include "mqtt_callback.h"
#include <Arduino.h>

// Definindo pinos e frequências
const int pwmFreq = 20000;  // Frequência de 20kHz
const int pwmResolution = 8; // Resolução de 8 bits (0-255)
const int pinoRS2 = 32;

void setupPWM() {
  ledcAttach(pinoRS2, pwmFreq, pwmResolution);
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  Serial.print("Mensagem recebida [");
  Serial.print(topic);
  Serial.print("]: ");
  Serial.println(message);

  int brilho = constrain(message.toInt(), 0, 100); // Garantir que está entre 0-100

  // Mapear o brilho de 0–100 para 0–255 (escala de 8 bits)
  int pwm = (255.0 / 100.0) * brilho;

  if (strcmp(topic, "lampada/brilho") == 0) {
    ledcWrite(pinoRS2, pwm);
  }
}
