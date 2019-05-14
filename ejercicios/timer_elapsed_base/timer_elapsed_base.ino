/*
  Activación de temporizadores mediante librería elapsedMillis
  Código base de muestra con 2 tareas ejecutadas a diferentes intervalos
*/

#include <elapsedMillis.h>

const byte LED = 2;
const unsigned int INTERVALO1 = 1000, INTERVALO2 = 3000;

unsigned long contador = 0;

// Generamos 2 objectos para manejar 2 intervalos de tiempo
elapsedMillis timer1;
elapsedMillis timer2;

void setup() {
  Serial.begin(38400);
  pinMode(LED, OUTPUT);
}

void loop() {
  // Si timer1 supera el intervalo1, alternamos el led y volvemos timer1 a 0
  if (timer1 >= INTERVALO1) {
    digitalWrite(LED, !digitalRead(LED));
    timer1 = 0;
  }

  // Si timer2 supera el intervalo2, incrementamos el contador y volvemos timer2 a 0
  if (timer2 >= INTERVALO2) {
    contador++;
    Serial.println(contador);
    timer2 = 0;
  }
}
