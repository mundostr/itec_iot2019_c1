/*
  Ejemplo de uso del sensor de temperatura Dallas ds18b20 con protocolo OneWire.
*/

#include <WiFi.h>
#include <Ticker.h>
#include <OneWire.h>
#include <DallasTemperature.h>

const byte LED = 2;
const byte ONEWIRE = 23;
const int FREC_SENSOR = 100;
const byte LIMITE_TEMP = 25;
const char* REDWF = "APIOT";
const char* CLAVE = "arduino2019";

Ticker ctrlSensor;
OneWire oneWire(ONEWIRE);
DallasTemperature sensors(&oneWire);

void conectarWiFi() {
  WiFi.begin(REDWF, CLAVE);
  Serial.println("Conectando a " + String(REDWF));
  while (WiFi.status() != WL_CONNECTED) {}
  Serial.println("OK! ");
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
}

void leerSensor() {
  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);
  temperatura > LIMITE_TEMP ? digitalWrite(LED, HIGH) : digitalWrite(LED, LOW);
  Serial.println(temperatura);
}

void setup() {
  Serial.begin(115200);
  Serial.println("SISTEMA INICIADO");
  pinMode(LED, OUTPUT);
  sensors.begin();
  conectarWiFi();
  ctrlSensor.attach_ms(FREC_SENSOR, leerSensor);
}

void loop() {
}
