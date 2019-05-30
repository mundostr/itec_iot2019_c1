/*
  https://github.com/me-no-dev/AsyncTCP
  https://github.com/me-no-dev/ESPAsyncWebServer
  Ejemplo de servidor web básico operando como punto de acceso (AP)
*/

#include <WiFi.h>
#include <DHTesp.h>
#include <ESPAsyncWebServer.h>

const byte PIN_DHT = 17;
// Configuramos a voluntad un par de constantes para el ID de red y clave que deseemos
const char* REDWF = "AP23";
const char* CLAVE = "arduino2019";

DHTesp dht;
AsyncWebServer servidor(80);

void setup() {
  Serial.begin(115200);
  dht.setup(PIN_DHT, DHTesp::DHT11);
  Serial.println("SISTEMA INICIADO");
  Serial.println();

  activarWiFi();
  activarServidor();
}

void loop() {
}

void activarWiFi() {
  Serial.println("Activando red " + String(REDWF));
  // Simplemente en lugar de conectarnos como cliente a un AP que ya existe (utilizando el método begin()),
  // creamos nuestro propio AP con el método softAP(). Por defecto el IP que aplica softAP() es el
  // 192.168.4.1, pero podemos modificarlo fácilmente con el siguiente código:
  // IPAddress ipMod(192, 168, 4, 10);
  // IPAddress mascaraMod(255, 255, 255, 0);
  // WiFi.softAPConfig(ipMod, ipMod, mascaraMod);
  
  while (!WiFi.softAP(REDWF, CLAVE)) {}
  Serial.println("OK! ");
  Serial.println(WiFi.softAPmacAddress());
  Serial.println(WiFi.softAPIP());
}

void activarServidor() {
  servidor.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/html", "Servidor activo en <b>" + String(WiFi.macAddress()) + "</b>");
  });

  servidor.on("/dht", HTTP_GET, [](AsyncWebServerRequest * request) {
    String cadena;

    if (request->args() > 0) {
      byte indice;
      int argumento = request->arg(indice = 0).toInt();
      cadena = "<h1 style=\"color: #f60; font-family: Arial; font-weight: bold;\">Lectura del sensor: <b>" + String(leerDHT(argumento)) + "</b></h1>";
    } else {
      cadena = "Se requieren argumentos: <b>?lectura=0|1</b>";
    }

    request->send(200, "text/html", cadena);
  });

  servidor.begin();
}

float leerDHT(byte dato) {
  TempAndHumidity lectura = dht.getTempAndHumidity();
  if (dato == 0) {
    return lectura.temperature;
  } else  if (dato == 1) {
    return lectura.humidity;
  } else {
    return -1;
  }
}
