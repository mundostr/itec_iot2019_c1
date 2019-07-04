/*
  Ejemplo de publicación directa en canal de Telegram mediante
  librería UniversalTelegramBot.
  ATENCION!: esta librería utiliza ArduinoJson V5
*/

#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

const boolean DEBUG = true;
const char *WIFI_SSID = "APIOT";
const char *WIFI_CLAVE = "arduino2019";

#define BOTtoken "643154787:AAED3nD7Zx2HdVVEtRMSlfKtJXm2QbrqjlY"

WiFiClientSecure cliente;
UniversalTelegramBot bot(BOTtoken, cliente);

void consola(String mensaje, boolean salto = true) {
  if (DEBUG) {
    if (salto) {
      Serial.println(mensaje);
    } else {
      Serial.print(mensaje);
    }
  }
}

void conectarWifi() {
  WiFi.begin(WIFI_SSID, WIFI_CLAVE);

  consola("Conectando Wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    consola(".", false);
  }
  consola(" OK!");
  consola(WiFi.localIP().toString());
}

void setup() {
  if (DEBUG) {
    Serial.begin(115200);
    consola("SISTEMA INICIADO");
  }

  conectarWifi();
  enviarMensaje("637803697", "Mensaje de prueba: " + String(millis()));
}

void loop() {
}

void enviarMensaje(String idDestino, String mensaje) {
  if (bot.sendMessage(idDestino, mensaje, "")) {
    consola("Mensaje enviado");
  } else {
    consola("ERROR al enviar mensaje");
  }
}
