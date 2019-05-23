#include <WiFi.h>
#include <HTTPClient.h>

const char *REDWF = "APIOT";
const char *CLAVEWF = "arduino2019";

void setup() {
  Serial.begin(115200);
  Serial.println("SISTEMA INICIADO");
  Serial.println();

  conectarWiFi();
  // http://mundostreaming.tv/itec/arduino/clima.php
  // http://api.openweathermap.org/data/2.5/find?q=rafaela&mode=json&units=metric&lang=sp&APPID=bbbe84df6ab458740a22a2e0a1eb7663
  enviarPeticion("http://mundostreaming.tv/itec/arduino/clima.php");
}

void loop() {
}

void conectarWiFi() {
  WiFi.begin(REDWF, CLAVEWF);

  while (WiFi.status() != WL_CONNECTED) {}
  Serial.println("OK! ");
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
}

void enviarPeticion(String ruta) {
  Serial.println("Enviando peticion a " + ruta);

  HTTPClient http;
  http.begin(ruta);
  int httpCode = http.GET();
  if (httpCode > 0) {
    Serial.println("[HTTP] GET... codigo: " + String(httpCode));

    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      // Serial.println(payload);
      Serial.println("Temperatura: " + payload.substring(0, 5));
    }
  } else {
    Serial.println("[HTTP] GET... error: " + String(http.errorToString(httpCode).c_str()));
  }

  http.end();
}
