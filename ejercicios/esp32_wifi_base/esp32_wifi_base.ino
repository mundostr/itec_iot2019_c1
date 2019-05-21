/*
  ESP32, interfaz Wifi base - escaneo de redes y conexión inicial
*/

#include <WiFi.h>
#include "funciones.h"

void setup() {
  Serial.begin(115200);
  Serial.println("SISTEMA INICIADO");
  Serial.println();

  // buscarRedes();
  conectarWiFi();
}

void loop() {
}
