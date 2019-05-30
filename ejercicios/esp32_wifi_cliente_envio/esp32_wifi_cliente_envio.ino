#include <WiFi.h>
#include <HTTPClient.h>

const char* RED_WF = "APIOT";
const char* CLAVE_WF =  "arduino2019";

void setup() {
  Serial.begin(115200);
  conectarWF();
}

void loop() {
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
  HTTPClient http;

  http.begin("http://dweet.io/dweet/for/itec_sensor_44?m=" + String(millis()));
  
  int codigoRespuesta = http.GET();
  Serial.println("Respuesta: " + String(codigoRespuesta));
  if (codigoRespuesta > 0) {
    String respuesta = http.getString();
    Serial.println(respuesta);
  } else {
    Serial.print("ERROR al enviar solicitud: ");
  }

  http.end();
}
