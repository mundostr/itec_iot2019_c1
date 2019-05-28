/*
  https://github.com/me-no-dev/AsyncTCP
  https://github.com/me-no-dev/ESPAsyncWebServer
*/

#include <ESPAsyncWebServer.h>

String cadena;
const char* REDWF = "APIOT";
const char* CLAVE = "arduino2019";
enum colores { ROJO, VERDE, AZUL, AMARILLO, MAGENTA, APAGADO };

AsyncWebServer servidor(80);

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

void cambiarColorLedM(byte led, colores color) {
  // ledM.clear();
  // En el switch vemos la comodidad de utilizar las constantes especificadas mediante "enum"
  switch (color) {
    case ROJO:
      // Recordar que estamos utilizando NEO_GRB
      ledM.setPixelColor(led, 0, 255, 0);
      break;

    case VERDE:
      ledM.setPixelColor(led, 255, 0, 0);
      break;

    case AZUL:
      ledM.setPixelColor(led, 0, 0, 255);
      break;

    case APAGADO:
      ledM.setPixelColor(led, 0);
      break;
  }

  ledM.show();
}

void activarServidor() {
  servidor.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    String respuesta = "Servidor activo en <b>" + String(WiFi.macAddress()) + "</b>";
    request->send(200, "text/html", respuesta);
  });

  servidor.on("/rojo", HTTP_GET, [](AsyncWebServerRequest * request) {
    cambiarColorLedM(0, ROJO);
    request->send(200, "text/plain", "Led cambiado a rojo");
  });

  servidor.on("/verde", HTTP_GET, [](AsyncWebServerRequest * request) {
    cambiarColorLedM(0, VERDE);
    request->send(200, "text/plain", "Led cambiado a verde");
  });

  servidor.on("/apagar", HTTP_GET, [](AsyncWebServerRequest * request) {
    cambiarColorLedM(0, APAGADO);
    request->send(200, "text/plain", "Led apagado");
  });

  servidor.on("/ledm", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (request->args() > 0) {
      byte indice;
      int argumento = request->arg(indice = 0).toInt();
      if (argumento == 0) {
        cambiarColorLedM(0, ROJO);
      } else if (argumento == 1) {
        cambiarColorLedM(0, VERDE);
      } else if (argumento == 5) {
        cambiarColorLedM(0, APAGADO);
      } else {
        cadena = "Se requieren argumentos: ?color=0|1|5";
      }
    } else {
      cadena = "Se requieren argumentos: ?color=0|1|5";
    }

    request->send(200, "text/plain", cadena);
  });

  servidor.on("/dhtt", HTTP_GET, [](AsyncWebServerRequest * request) {
    cadena = "Temperatura: " + String(leerDHT(0));
    request->send(200, "text/plain", cadena);
  });

  servidor.on("/dhth", HTTP_GET, [](AsyncWebServerRequest * request) {
    cadena = "Humedad: " + String(leerDHT(1));
    request->send(200, "text/plain", cadena);
  });

  servidor.onNotFound([](AsyncWebServerRequest * request) {
    request->send(404, "text/plain", "El punto de acceso no existe");
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
