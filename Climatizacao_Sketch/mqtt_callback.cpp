//Mensagens do MQTT são recebidas aqui, nossas mensagens são de texto simples a função callback aqui lé a mensagem
//e a reescreve na variável message que é uma string. E a imprime para debug.
#include "mqtt_callback.h"

const int pinoRELE = 0;


void callback(char* topic, byte* payload, unsigned int length) {
	String message = "";
	for (unsigned int i = 0; i < length; i++) {
		message += (char)payload[i];
	}

	Serial.print("Mensagem recebida [");
	Serial.print(topic);
	Serial.print("]: ");
	Serial.println(message);

	if (strcmp(topic, "climatização/rele") == 0) {
		if (message == "1") {
			digitalWrite(pinoRELE, HIGH);
		} else if (message == "0") {
			digitalWrite(pinoRELE, LOW);
		}
	}
}
