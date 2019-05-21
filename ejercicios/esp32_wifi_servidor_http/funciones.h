#include <ESPAsyncWebServer.h>

const char* REDWF = "APIOT";
const char* CLAVE = "itec2019";

AsyncWebServer servidor(80);

void activarServidor() {
  servidor.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/plain", "Servidor activo");
  });

  servidor.begin();
}

void conectarWiFi() {
  WiFi.begin(REDWF, CLAVE);

  Serial.println("Conectando a " + String(REDWF));
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("OK! ");
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
}
