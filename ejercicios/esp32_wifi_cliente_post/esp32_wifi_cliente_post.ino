/*
  Cliente HTTP para envío de datos a servidor externo
*/

#include <WiFi.h>
#include <HTTPClient.h>

const char *REDWF = "APIOT";
const char *CLAVEWF = "arduino2019";

void setup() {
  Serial.begin(115200);
  Serial.println("SISTEMA INICIADO");
  Serial.println();

  conectarWiFi();
  String datosJson = "{ \"datos\": \"23.02|23.28|22.98|23.01|22.91|24.05\" }";
  enviarDatos("http://mstr16.mundostreaming.tv:8095/iot", datosJson);
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

void enviarDatos(String ruta, String contenido) {
  Serial.println("Enviando peticion a " + ruta);

  HTTPClient http;
  http.begin(ruta);
  http.addHeader("Content-Type", "application/json");

  int respuestaHttp = http.POST(contenido);
  if (respuestaHttp > 0) {
    Serial.println("[HTTP] POST... codigo: " + String(respuestaHttp));

    if (respuestaHttp == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    }
  } else {
    Serial.println("[HTTP] POST... error: " + String(http.errorToString(respuestaHttp).c_str()));
  }

  http.end();
}
