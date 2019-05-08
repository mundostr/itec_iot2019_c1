/*
  Ejemplo de manejo de pulsador con antirrebote mediante librería
  También podemos ver el uso de un condicional simple en la verificación de estado del pulsador
  Recordemos que el condicional simple es de uso muy habitual en el control de estado de un pin digital
*/

// Inclusión de la librería Bounce2 para manejo del pulsador
#include <Bounce2.h>

#define PULSADOR 21

// Creación de un objeto de tipo Bounce, llamado pulsador1
// Bounce es el nombre de la clase correspondiente definida en la librería
Bounce pulsador1 = Bounce();

void setup() {
  // Activación de la consola serie para logueo de datos
  Serial.begin(38400);
  // Asignación del pin al pulsador, habilitando el pullup interno (en el ESP32 podemos usar también INPUT_PULLDOWN)
  // En realidad esto dependerá del pin elegido, revisar los esquemas para verificar cuáles tienen
  // resistencias de pullup y de pulldown disponibles.
  // Obviamente siempre podemos optar por configurar el pin como INPUT y conectar manualmente una resistencia externa.
  pulsador1.attach(PULSADOR, INPUT_PULLUP);
  // Activación de un pequeño intervalo de espera para evitar cualquier rebote del pulsador
  pulsador1.interval(30);
}

void loop() {
  // En el loop utilizamos constantemente el método update() de la librería para
  // actualizar la lectura del botón.
  pulsador1.update();
  // y finalmente aplicamos el método fell() para detectar el evento de cambio
  // de estado alto al bajo (recordar que estamos utilizando INPUT_PULLUP, con lo cual la lógica queda negada)
  // Si pasáramos a usar INPUT_PULLDOWN, el método a usar sería rose(), que se dispara cuando el pulsador
  // cambia de estado bajo a alto, en ese caso pasaríamos a trabajar con lógica directa.
  if (pulsador1.fell()) {
    // Vemos la aplicación de un condicional simple para verificar el estado del pulsador.
    Serial.println("Pulsado");
  }

  // Recordemos que también podemos usar un condicional excluyente para ejecutar selectivamente
  // un paquete de acciones en uno u otro estado
  // if (pulsador1.fell()) {
  //   Serial.println("Pulsado");
  // } else {
  //   Serial.println("Libre");
  // }
}
