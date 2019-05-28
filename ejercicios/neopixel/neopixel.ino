/*
  Un simple ejemplo de uso de leds programables mediante librería de Adafruit
  El led debe ser compatible Neopixel, como los PL9823
*/

#include <Adafruit_NeoPixel.h>

const byte MULTILED = 16;
// Enum nos permite definir un tipo de variable personalizado ("colores" en este caso)
// que acepta solo un paquete de constantes para identificar distintos estados.
// Es muy útil en la escritura de switch cases por ejemplo.
enum colores { ROJO, VERDE, AZUL, AMARILLO, MAGENTA, APAGADO };

// Definimos un objeto "ledM" de tipo Adafruit_NeoPixel
// NEO_GRB y NEO_KHZ800 son constantes ya especificadas en la librería, que dependen
// del tipo de led programable que utilicemos, en este caso se ajustan al PL9823
Adafruit_NeoPixel ledM = Adafruit_NeoPixel(1, MULTILED, NEO_GRB + NEO_KHZ800);

void setup() {
  // Solo inicializamos el led
  ledM.begin();
}

void loop() {
  // y en el loop() llamamos cíclicamente a la función que internamente ejecuta el código de cambio de color
  cambiarColorLedM(0, ROJO);
  delay(3000);
  cambiarColorLedM(0, VERDE);
  delay(3000);
  cambiarColorLedM(0, AZUL);
  delay(3000);
  cambiarColorLedM(0, APAGADO);
  delay(3000);
}

// La función recibe 2 argumentos, el primero indica el led destino, y el segundo el color.
// Lo del led destino se especifica ya que este tipo de leds pueden trabajar en cadena, si
// por ejemplo tenemos 10 leds PL9823 conectados en serie a través de su pata de enlace,
// los mismos se identifican del 0 al 9, es decir, si queremos encender el anteúltimo led,
// debemos llamar a la función utilizando como primer argumento el número 8.
// Por último vemos que el 2do argumento es de tipo "colores". "colores" existe como tipo
// de dato ya que lo hemos definido arriba mediante "enum", y solo aceptará uno de los valores
// en su lista (en este ejemplo serían ROJO, VERDE, AZUL, AMARILLO, MAGENTA), cualquier otro
// valor que pasemos, generará un error.
void cambiarColorLedM(byte led, colores color) {
  ledM.clear();
  // En el switch vemos la comodidad de utilizar las constantes especificadas mediante "enum"
  switch (color) {
    case ROJO:
      // Recordar que estamos utilizando NEO_GRB
      ledM.setPixelColor(led, 0, 255, 0);
      break;

    case VERDE:
      ledM.setPixelColor(led, 255, 0, 0);
      break;

    case AZUL:
      ledM.setPixelColor(led, 0, 0, 255);
      break;

    case APAGADO:
      ledM.setPixelColor(led, 0);
      break;
  }
  ledM.show();
}
