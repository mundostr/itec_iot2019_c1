#include <ESPAsyncWebServer.h>

const char* REDWF = "APIOT";
const char* CLAVE = "arduino2019";

AsyncWebServer servidor(80);

void activarServidor() {
  servidor.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    String respuesta = "Servidor activo en " + String(WiFi.macAddress());
    request->send(200, "text/plain", respuesta);
  });

  servidor.begin();
}

void conectarWiFi() {
  WiFi.begin(REDWF, CLAVE);

  Serial.println("Conectando a " + String(REDWF));
  while (WiFi.status() != WL_CONNECTED) {}
  Serial.println("OK! ");
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
}
