/*
  Sensado simple de datos mediante sensor DHT
  Simulación de comandos remotos utilizando consola serial y agregado de advertencia vía buzzer
*/

#include <DHTesp.h>
#include <Ticker.h>

const byte PIN_DHT = 17;
const byte PIN_BUZZER = 16;
const int FREC_LECTURA_SENSOR = 2000;
const int FREC_LECTURA_CONSOLA = 100;

#include "buzzer.h"

DHTesp dht;
Ticker ctrlSensor;
Ticker ctrlConsola;

void leerSensor() {
  TempAndHumidity lectura = dht.getTempAndHumidity();
  Serial.println("T: " + String(lectura.temperature) + ", H: " + String(lectura.humidity));
  if (lectura.humidity > 85) {
    tono(255);
  } else {
    tono(0);
  }
}

void leerConsola() {
  char lectura;
  if (Serial.available() > 0) {
    lectura = Serial.read();
    switch (lectura) {
      case 105: // i
        Serial.println("Lectura activa");
        ctrlSensor.attach_ms(FREC_LECTURA_SENSOR, leerSensor);
        break;

      case 100: // d
        Serial.println("Lectura inactiva");
        ctrlSensor.detach();
        tono(0);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("SISTEMA ACTIVO");
  Serial.println("i = inicia, d = detiene");

  pinMode(PIN_BUZZER, OUTPUT);
  setearBuzzer();
  dht.setup(PIN_DHT, DHTesp::DHT11);
  ctrlConsola.attach_ms(FREC_LECTURA_CONSOLA, leerConsola);
}

void loop() {
}
