/*
  Ejemplo de lectura analógica de alto nivel con ajuste de desviación
  https://arachnoid.com/polysolve/
*/

const byte HALL = 36, MUESTRAS = 100;

int lectura;
double lecturaAjustada;

// pow es una función heredada de C que eleva un número a una potencia.
// Sin embargo la implementación en Arduino de esta función es muy lenta para su utilización en lectura constante de sensores.
// por lo cual en estos casos es recomendable realizar la multiplicación directa (pow(x, 2) = x * x).
double f(int x) {
  return  5.1601847963474616e+006
          + -7.5357313112322236e+003 * x
          +  3.1876201534341031e+000 * x * x
          + -3.2509908818410539e-004 * x * x * x
          +  2.8588633399737014e-007 * x * x * x * x
          + -2.4808400362364693e-010 * x * x * x * x * x
          +  4.8875739130208339e-014 * x * x * x * x * x * x;
}

void setup() {
  Serial.begin(1000000);
  pinMode(HALL, INPUT);
  delay(5000);
  for (int i = 0; i < MUESTRAS; i++) {
    lectura = analogRead(HALL);
    lecturaAjustada = f(lectura);
    Serial.println(String(lectura) + "," + String(lecturaAjustada));
    delay(50);
  }
}

void loop() {
}
