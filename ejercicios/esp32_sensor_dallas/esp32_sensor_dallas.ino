/*
  Ejemplo de uso del sensor de temperatura Dallas ds18b20 con protocolo OneWire.
*/

#include <WiFi.h>
#include <Ticker.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_NeoPixel.h>

const byte ONEWIRE = 15;
const byte MULTILED = 16;
const int FREC_SENSOR = 250;
const byte LIMITE_TEMP = 29;
const char* REDWF = "APIOT";
const char* CLAVE = "arduino2019";
enum condiciones {BAJA, NORMAL, ALTA };

Ticker ctrlSensor;
OneWire oneWire(ONEWIRE);
DallasTemperature sensors(&oneWire);
Adafruit_NeoPixel ledM = Adafruit_NeoPixel(1, MULTILED, NEO_GRB + NEO_KHZ800);
condiciones condicionTemperatura = NORMAL;
condiciones condicionTemperaturaPrevia = NORMAL;

void encenderLed(byte led, condiciones temperatura) {
  ledM.clear();
  switch (temperatura) {
    case NORMAL:
      ledM.setPixelColor(led, 255, 0, 0);
      break;

    case ALTA:
      ledM.setPixelColor(led, 0, 255, 0);
      break;
  }
  ledM.show();
}

void conectarWiFi() {
  encenderLed(0, ALTA);
  WiFi.begin(REDWF, CLAVE);

  Serial.println("Conectando a " + String(REDWF));
  while (WiFi.status() != WL_CONNECTED) {}
  encenderLed(0, NORMAL);
  Serial.println("OK! ");
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
}

void leerSensor() {
  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);
  temperatura > LIMITE_TEMP ? condicionTemperatura = ALTA : condicionTemperatura = NORMAL;
  if (condicionTemperatura != condicionTemperaturaPrevia) {
    encenderLed(0, condicionTemperatura);
    condicionTemperaturaPrevia = condicionTemperatura;
  }
  Serial.println(temperatura);
}

void setup() {
  Serial.begin(115200);
  Serial.println("SISTEMA INICIADO");
  ledM.begin();
  sensors.begin();
  conectarWiFi();
  ctrlSensor.attach_ms(FREC_SENSOR, leerSensor);
}

void loop() {
}
