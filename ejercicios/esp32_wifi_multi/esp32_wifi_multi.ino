/*
  ESP32, interfaz Wifi con configuraciones múltiples - escaneo de redes y conexión inicial
*/

#include <WiFi.h>
#include <WiFiMulti.h>
#include "funciones.h"

void setup() {
  Serial.begin(115200);
  Serial.println("SISTEMA INICIADO");
  Serial.println();

  configurarWiFi();
  conectarWiFi();
}

void loop() {
}
