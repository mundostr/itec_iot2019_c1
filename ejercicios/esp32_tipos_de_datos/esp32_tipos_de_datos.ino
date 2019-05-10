/*
  Detalle tipos de datos en ESP32
*/

#include <Arduino.h>

void mostrar(const char * tag, int l) {
  Serial.print(tag);
  Serial.print("\t"); // Recordar que \t inserta una tabulación
  Serial.println(l);
}

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println();

  // sizeof es una función propia de C, que recibe un único argumento
  // (nombre de una variable o nombre de un tipo de dato)
  // y devuelve su tamaño en bytes
  mostrar("bool", sizeof(bool));
  mostrar("boolean", sizeof(boolean));
  mostrar("byte", sizeof(byte));
  mostrar("char", sizeof(char));
  mostrar("unsigned char", sizeof(unsigned char));
  mostrar("uint8_t", sizeof(uint8_t));
  mostrar("short", sizeof(short));
  mostrar("uint16_t", sizeof(uint16_t));
  mostrar("word", sizeof(word));
  mostrar("int", sizeof(int));
  mostrar("unsigned int", sizeof(unsigned int));
  mostrar("size_t", sizeof(size_t));
  mostrar("float", sizeof(float));
  mostrar("long", sizeof(long));
  mostrar("unsigned long", sizeof(unsigned long));
  mostrar("uint32_t", sizeof(uint32_t));
  mostrar("double", sizeof(double));
  mostrar("long long", sizeof(long long));
  mostrar("unsigned long long", sizeof(unsigned long long));
  mostrar("uint64_t", sizeof(uint64_t));
}

void loop() {
}
