/*
  Control de tareas propio de ESP32 mediante Ticker
*/

#include <Ticker.h>

const byte LED = 2;
const byte SENSOR = 17;

// Generamos el objeto para manejar cada tarea
Ticker ctrlLed;
Ticker ctrlSensor;

void alternarLed() {
  digitalWrite(LED, !digitalRead(LED));
}

void leerSensor() {
  // Acá colocamos la secuencia de lectura y asignamos las variables que correspondan
}

void setup() {
  pinMode(LED, OUTPUT);
  // Asignamos la tarea, indicando frecuencia y función que debe ejecutar
  // Podemos utilizar attach() con frecuencia en segs directamente en lugar de ms
  // y los métodos once_ms() / once() si queremos ejecutar la tarea solo una vez.
  ctrlLed.attach_ms(100, leerSensor);
  ctrlLed.attach_ms(1000, alternarLed);
}

void loop() {
  // Como vemos el loop() queda vacío, el propio sistema esp_timer interno
  // del ESP32 se encarga de mantener las tareas funcionando
}
