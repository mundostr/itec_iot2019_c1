/*
  https://github.com/me-no-dev/AsyncTCP
  https://github.com/me-no-dev/ESPAsyncWebServer
  Ejemplo de servidor web básico, con utilización de puntos de acceso comunes,
  argumentos vía URL y lectura de sensor bajo demanda
*/

#include <WiFi.h>
#include <DHTesp.h>
// #include <SPIFFS.h>
#include <Adafruit_NeoPixel.h>

const byte MULTILED = 16;
const byte PIN_DHT = 17;

DHTesp dht;
Adafruit_NeoPixel ledM = Adafruit_NeoPixel(1, MULTILED, NEO_GRB + NEO_KHZ800);
#include "funciones.h"

void setup() {
  Serial.begin(115200);
  ledM.begin();
  dht.setup(PIN_DHT, DHTesp::DHT11);

  //  if (!SPIFFS.begin()) {
  //    Serial.println("ERROR al montar SPIFFS");
  //    while(1);
  //  }

  Serial.println("SISTEMA INICIADO");
  Serial.println();

  conectarWiFi();
  activarServidor();
}

void loop() {
}
