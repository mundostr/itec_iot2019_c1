/*
  https://github.com/me-no-dev/AsyncTCP
  https://github.com/me-no-dev/ESPAsyncWebServer
*/

#include <WiFi.h>
#include "funciones.h"

void setup() {
  Serial.begin(115200);
  Serial.println("SISTEMA INICIADO");
  Serial.println();

  conectarWiFi();
  activarServidor();
}

void loop() {
}
