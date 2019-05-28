/*
  Código simple para identificar la dirección MAC del WF
  https://macvendors.com/
*/

#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_MODE_AP);
  Serial.println("SISTEMA INICIADO");
  Serial.println(WiFi.softAPmacAddress());
}

void loop() {
}
