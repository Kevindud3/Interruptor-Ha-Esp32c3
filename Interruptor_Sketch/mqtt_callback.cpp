//Mensagens do MQTT são recebidas aqui, nossas mensagens são de texto simples a função callback aqui lé a mensagem
//e a reescreve na variável message que é uma string. E a imprime para debug.
#include "mqtt_callback.h"

// Definindo pinos e frequências
const int pwmFreq = 20000;  // Frequência de 20kHz
const int pwmResolution = 8; // Resolução de 8 bits (0-255)
const int pinoPWM = 10;
const int pinoRELE = 0;

void setupPWM() {
	ledcAttach(pinoPWM, pwmFreq, pwmResolution);
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


	// Mapear o brilho de 0–100 para 0–255 (escala de 8 bits)

	if (strcmp(topic, "lampada/brilho") == 0) {
		int brilho = constrain(message.toInt(), 0, 100); // Garantir que está entre 0-100
		int pwm = (255.0 / 100.0) * brilho;
		Serial.println(pwm);
		ledcWrite(pinoPWM, pwm);
	}
	else if (strcmp(topic, "interruptor/switch") == 0) {
		if (message == "1") {
			digitalWrite(pinoRELE, HIGH);
		} else if (message == "0") {
			digitalWrite(pinoRELE, LOW);
		}
	}

	else if (strcmp(topic, "interruptor/sleep") == 0) {
		if (message == "1") {
			goToDeepSleep(3);
		}
	}
}
