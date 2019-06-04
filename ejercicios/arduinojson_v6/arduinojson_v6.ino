/*
  Ejemplo de parseo de datos JSON mediante librería ArduinoJson versión 6
  IMPORTANTE!: verificar que se utiliza la versión correcta, ya que en anteriores
  la estructura de código es diferente, la V6 ha simplificado esta situación.
*/
#include <ArduinoJson.h>

// Este es el paquete json que necesitamos parsear, el cual obviamente en condiciones
// habituales va a llegar como respuesta a una solicitud en un servidor externo.
// Dado que el formato json válido utiliza comillas internamente para delimitar cada
// propiedad, es importante escapar dichas comillas estén \"escapadas\" para poder
// asignar correctamente la cadena en Arduino.
String datosJson = "{ \"sensor\": \"Rafaela03\", \"temperatura\": 28.54, \"presion\": 1018.60, \"humedad\": 84.12 }";

void setup() {
  Serial.begin(115200);

  // Generamos un buffer estático para almacenar temporalmente y procesar la cadena
  // Lo ideal es reservar solo el espacio necesario, que puede calcularse en
  // https://arduinojson.org/v6/assistant/, según la cadena a recibir
  DynamicJsonDocument docJson(109);
  DeserializationError errorJson = deserializeJson(docJson, datosJson);
  if (errorJson) {
    Serial.println("Error al interpretar la cadena JSON");
  } else {
    String sensor = docJson["sensor"];
    String temperatura = docJson["temperatura"];
    String presion = docJson["presion"];
    String humedad = docJson["humedad"];

    Serial.println("S: " + sensor);
    Serial.println("T: " + temperatura);
    Serial.println("P: " + presion);
    Serial.println("H: " + humedad);
  }
}

void loop() {
}
