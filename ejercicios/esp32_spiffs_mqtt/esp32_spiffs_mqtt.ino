#include <WiFi.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>

const char* ID_WIFI = "APIOT";
const char* CL_WIFI =  "arduino2019";

AsyncWebServer servidor(80);

void setup() {
  Serial.begin(115200);

  montarArchivos();
  conectarWifi();
  habilitarServidor();
}

void loop() {
}

void montarArchivos() {
  if (!SPIFFS.begin(false)) {
    Serial.println("Error al montar el sistema de archivos");
    return;
  }
  Serial.println("SISTEMA DE ARCHIVOS MONTADO");
}

void conectarWifi() {
  Serial.println("Conectando Wifi");

  WiFi.begin(ID_WIFI, CL_WIFI);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }

  Serial.println(WiFi.localIP());
}

void habilitarServidor() {
  servidor.on("/mqtt", HTTP_GET, [](AsyncWebServerRequest * solicitud) {
    solicitud->send(SPIFFS, "/mqtt.html", "text/html");
  });

  servidor.begin();
  
  Serial.println("Servidor http activo");
}
