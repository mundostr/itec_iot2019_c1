/*
  Ejemplo de envío simple http a servidor externo utilizando HTTPClient
*/

#include <WiFi.h>
#include <HTTPClient.h>

const char* RED_WF = "APIOT";
const char* CLAVE_WF =  "arduino2019";

void setup() {
  Serial.begin(115200);
  conectarWF();
}

void loop() {
  // Cada 30 segs chequeamos si estamos online en la conexión WF, si es así sensamos y enviamos, sino reconectamos
  if (WiFi.status() == WL_CONNECTED) {
    sensarYEnviar();
  } else {
    conectarWF();
  }

  delay(30000);
}

void conectarWF() {
  Serial.println("Conectando a " + String(RED_WF));
  WiFi.begin(RED_WF, CLAVE_WF);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println(".");
  }
  Serial.println("OK!");
  Serial.println(WiFi.localIP());
}

void sensarYEnviar() {
  // Dentro de la propia función de sensado y envío, generamos el objeto para la conexión http
  HTTPClient http;

  // Nos conectamos en este caso a un servidor Dweet para enviar rápidamente un dato
  // sin necesidad de registrar ninguna cuenta, validarnos, etc.
  // itec_sensor_44 y el argumento valor1 son por supuesto generados a nuestro gusto,
  // podemos colocar cualquier nombre de dweet y funcionará sin problemas, excepto lógicamente
  // que estuviese siendo ya aplicado por otro usuario en ese momento.
  http.begin("http://dweet.io/dweet/for/itec_sensor_44?valor1=" + String(millis()));

  // Para leer por navegador el último dato recibido por el dweet, empleamos la dirección
  // https://dweet.io/get/latest/dweet/for/itec_sensor_44

  int codigoRespuesta = http.GET();
  Serial.println("Respuesta: " + String(codigoRespuesta));
  if (codigoRespuesta > 0) {
    // Si el código de respuesta es > 0, significa que la petición fue procesada
    String respuesta = http.getString();
    Serial.println(respuesta);
  } else {
    // Si es negativo, hubo un error
    Serial.print("ERROR al enviar solicitud: ");
  }

  // Bajamos el cliente hasta la próxima iteracción
  http.end();
}
