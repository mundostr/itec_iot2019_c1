/*
  https://github.com/me-no-dev/AsyncTCP
  https://github.com/me-no-dev/ESPAsyncWebServer
  Ejemplo de servidor web básico con autenticación y lectura de sensor bajo demanda
*/

#include <WiFi.h>
#include <DHTesp.h>
#include <ESPAsyncWebServer.h>

const byte PIN_DHT = 17;
const char* REDWF = "APIOT";
const char* CLAVE = "arduino2019";
const char* USUARIO_HTTP = "admin";
const char* CLAVE_HTTP = "itec";

DHTesp dht;
AsyncWebServer servidor(80);

void setup() {
  Serial.begin(115200);
  dht.setup(PIN_DHT, DHTesp::DHT11);
  Serial.println("SISTEMA INICIADO");
  Serial.println();

  conectarWiFi();
  activarServidor();
}

void loop() {
}

void conectarWiFi() {
  WiFi.begin(REDWF, CLAVE);

  Serial.println("Conectando a " + String(REDWF));
  while (WiFi.status() != WL_CONNECTED) {}
  Serial.println("OK! ");
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
}

void activarServidor() {
  servidor.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(200, "text/html", "Servidor activo en <b>" + String(WiFi.macAddress()) + "</b>");
    // En el contenido devuelto por nuestro servidor, no estamos limitados a texto plano,
    // podemos utilizar HTML, armando cualquier tag como por ejemplo el <b></b> que utilizamos
    // debajo para colocar la dirección MAC en negrita.

    // Otra alternativa es escribir directamente el contenido completo HTML de la página en una constante
    // de texto, utilizando const char pagina[] PROGMEM = "" para definirlo. No es la opción más práctica
    // si necesitamos editar el texto, pero funciona. Es conveniente pasar dicho texto por un par de
    // herramientas: https://www.willpeavy.com/minifier/ para minimizarlo y
    // http://tomeko.net/online_tools/cpp_text_escape.php?lang=en para escapar las comillas y convertirlo
    // en una cadena segura C.

    // Una tercer opción es entregar directamente archivos desde el sistema SPIFFS que puede ser habilitado
    // en el ESP32, ESPAsyncWebServer tiene soporte para este tipo de respuestas.
  });

  servidor.on("/privado", HTTP_GET, [](AsyncWebServerRequest * request) {
    if (!request->authenticate(USUARIO_HTTP, CLAVE_HTTP)) {
      return request->requestAuthentication();
    } else {
      request->send(200, "text/html", "Este contenido solo es visible para <b>usuarios validados</b>");
    }
  });

  servidor.on("/dht", HTTP_GET, [](AsyncWebServerRequest * request) {
    String cadena;

    if (request->args() > 0) {
      byte indice;
      // En este punto de acceso utilizamos argumentos, que podemos enviar en la URL y modifican
      // el comportamiento de la respuesta. El formato de la url es http://ip/dht?retorno=0
      // retorno puede estar en 0 o 1, lo único que hacemos en la línea siguiente es recuperarlo
      // desde la URL y asignarlo a "argumento", llamando luego a leerDHT(argumento) para que nos
      // devuelva temperatura o humedad
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
