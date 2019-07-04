/*
  https://github.com/yagop/node-telegram-bot-api
  http://www.yogasaikrishna.com/simple-restful-api-using-nodejs-express-and-mysql/
*/

#include <WiFi.h>
#include <HTTPClient.h>

const boolean DEBUG = true;
const char *WIFI_SSID = "APIOT";
const char *WIFI_CLAVE = "arduino2019";
// const String SRV_API_TELEGRAM = "http://mstr16.mundostreaming.tv:8095/iot/ntelegram";
const String SRV_API_MYSQL = "http://mstr16.mundostreaming.tv:8095/iot/nmysql";
float max_temperatura = 28.00;

void consola(String mensaje, boolean salto = true) {
  if (DEBUG) {
    if (salto) {
      Serial.println(mensaje);
    } else {
      Serial.print(mensaje);
    }
  }
}

void conectarWifi() {
  WiFi.begin(WIFI_SSID, WIFI_CLAVE);

  consola("Conectando Wifi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    consola(".", false);
  }
  consola(" OK!");
  consola(WiFi.localIP().toString());
}

void notificar(String ruta, String mensaje) {
  HTTPClient http;
  http.begin(ruta);
  http.addHeader("Content-Type", "application/json");

  int respuestaHttp = http.POST(mensaje);
  if (respuestaHttp > 0) {
    consola("[HTTP] POST... codigo: " + String(respuestaHttp));

    if (respuestaHttp == HTTP_CODE_OK) {
      String payload = http.getString();
      consola(payload);
    }
  } else {
    consola("[HTTP] POST... error: " + String(http.errorToString(respuestaHttp).c_str()));
  }

  http.end();
}

void setup() {
  if (DEBUG) {
    Serial.begin(115200);
  }
  consola("SISTEMA INICIADO");
  conectarWifi();

  // String mensaje = "{ \"destino\": \"637803697\", \"mensaje\": \"ATENCION!: temp max excedida -> ";
  // mensaje.concat(max_temperatura);
  // mensaje.concat(" C\" }");
  String mensaje="{ \"lectura\": \"" + String(millis()) + "\"}";
  // notificar(SRV_API_TELEGRAM, mensaje);
  notificar(SRV_API_MYSQL, mensaje);
}

void loop() {
}
