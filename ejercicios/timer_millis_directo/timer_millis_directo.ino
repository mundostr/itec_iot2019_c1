/*
  Ejemplo de habilitación de temporizadores mediante el uso directo de millis()
  Una forma muy sencilla de poder ejecutar distintas tareas a intervalos programados.
*/

const byte LED = 2;

// Defino variables de tipo long para los timers y las inicio en 0
unsigned long timer1 = 0, timer2 = 0;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  // El primer temporizador mantiene parpadeando el led onboard
  // en este caso 1 vez por segundo
  if (millis() - timer1 >= 1000) {
    digitalWrite(LED, !digitalRead(LED));
    // Ejecuto lo que tengo que ejecutar dentro y actualizo timer1 al millis() actual,
    // así el sistema queda listo para la próxima condición válida.
    timer1 = millis();
  }

  // El segundo temporizador se ejecuta en este caso cada 3 segundos (3000 ms)
  // Por supuesto podría agregar la cantidad de temporizadores que necesitara
  if (millis() - timer2 >= 3000) {
    // Contenido que se ejecuta acá
    timer2 = millis();
  }
}
