/*
  Temporizadores mediante librería elapsedMillis con
  agregado de tipo de dato enum para agrupar distintos estados de ejecución
  de máquina (State Machine). Uso de switch case para manejo de estados en loop().
*/

#include <elapsedMillis.h>

const byte LED = 2;
const int PERIODO_FUNCIONAMIENTO = 10000;
int frecParpadeo;

enum etapas { ESPERA, FUNCIONANDO, DETENIDO } estado;

elapsedMillis timer1;
elapsedMillis timer2;

void leerSerial() {
  if (Serial.available() > 0) {
    char lectura = Serial.read();
    if (lectura == 'f') {
      timer2 = 0;
      estado = FUNCIONANDO;
      Serial.println("funcionando");
    } else if (lectura == 'd') {
      estado = DETENIDO;
      Serial.println("detenido");
    } else if (lectura == 'e') {
      estado = ESPERA;
      Serial.println("en espera");
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  estado = ESPERA;
  Serial.println("en espera");
}

void loop() {
  switch (estado) {
    case ESPERA:
      frecParpadeo = 1000;
      leerSerial();
      break;

    case FUNCIONANDO:
      frecParpadeo = 250;
      leerSerial();
      break;

    case DETENIDO:
      frecParpadeo = 3000;
      break;
  }

  if (timer1 >= frecParpadeo) {
    digitalWrite(LED, !digitalRead(LED));
    timer1 = 0;
  }

  if (estado == FUNCIONANDO) {
    if (timer2 >= PERIODO_FUNCIONAMIENTO) {
      estado = DETENIDO;
      Serial.println("detenido");
      timer2 = 0;
    }
  }
}
