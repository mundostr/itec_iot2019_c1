/*
  Repaso uso matrices (definición, asignación y ciclado)
*/

const byte POT = 36;
const int MAX_LECTURAS = 100;

int contador = 0;
// definimos una matriz de elementos tipo entero (int), de un tamaño MAX_LECTURAS
// IMPORTANTE: siempre que sea posible, reservar un tamaño en la definición.
int mtrLecturas[MAX_LECTURAS];

bool calculoHecho = false;

// Una sencilla función, solo para repasar el concepto de definición y uso de funciones
// En este caso cicla la matriz, realizando la sumatoria de los items y devolviendo
// ese total como dato de tipo long
long sumatoria() {
  long total;
  for (byte i = 0; i < MAX_LECTURAS; i++) {
    total += mtrLecturas[i]; // o si se prefiere, total = total + mtrLecturas[i]n
  }
  return total;
}

void setup() {
  Serial.begin(115200);
  pinMode(POT, INPUT);
}

void loop() {
  // Practicamos el uso de condicionales. Solo realizamos 100 lecturas con esperas de 250 ms entre ellas.
  if (contador < MAX_LECTURAS) {
    // Asignamos la lectura del pot al item correspondiente en la matriz, imprimimos por consola e incrementamos el índice
    mtrLecturas[contador] = analogRead(POT);
    Serial.println(String(contador) + ": " + String(mtrLecturas[contador]));
    contador++;
    delay(250);
  } else {
    // Una vez que se terminen las lecturas, el sistema ejecutará esta sección.
    // Solo si la bandera booleana calculoHecho está en falso, imprime el valor devuelto por la función sumatoria()
    // y pasa el flag a true para que ya no vuelva a ejecutarse.
    if (!calculoHecho) {
      Serial.println(sumatoria());
      calculoHecho = true;
    }
  }
}
