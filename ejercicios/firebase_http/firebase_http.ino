/*
  Ejemplo de conexión directa a Firebase mediante librería
  https://github.com/mobizt/Firebase-ESP32
  Es necesario instalar la dependencia https://github.com/mobizt/HTTPClientESP32Ex
*/

#include <WiFi.h>
#include <FirebaseESP32.h>

const boolean DEBUG = true;
const char *WIFI_SSID = "ITEC - Publica";
const char *WIFI_CLAVE = "";
const char *FIREBASE_HOST = "remoto-itec.firebaseio.com";
const char *FIREBASE_SEC = "3XFWKpmBoKp83xEPYRxhGCDtQIjMumNA4uwHSzqv";

FirebaseData objFirebase;

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

void inicializarFirebase() {
  Firebase.begin(FIREBASE_HOST, FIREBASE_SEC);
  Firebase.reconnectWiFi(true);
  Firebase.setReadTimeout(objFirebase, 1000 * 60); // 1 minuto de timeout
  Firebase.setwriteSizeLimit(objFirebase, "tiny");
}

void publicarFirebase(String ruta, String cadena) {
  if (Firebase.pushJSON(objFirebase, ruta, cadena)) {
    consola("Contenido publicado en " + String(objFirebase.dataPath()) + "/" + String(objFirebase.pushName()));
  } else {
    consola("ERROR al publicar: " + String(objFirebase.errorReason()));
  }
}

void setup() {
  if (DEBUG) {
    Serial.begin(115200);
  }
  consola("SISTEMA INICIADO");
  conectarWifi();
  inicializarFirebase();
  publicarFirebase("/equipo11", "{ \"ts\": \"fecha y hora\", \"id_sensor\":\"14\", \"valor\": \"23.23\" }");
}

void loop() {
}
