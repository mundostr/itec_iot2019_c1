/*
  Ejemplo de estructura para manejo de sensor
*/

// Definimos una estructura "sensor" con todas las propiedades que nos interesen
// El objetivo de struct es generar una estructura de datos de diferentes tipos
// que puedan manejarse como unidad.
struct sensor {
  int id;
  int seccion;
  float lectura;
  String descripcion;
};

unsigned long contador;

// Definimos un objeto "sensor01" de tipo "sensor"
sensor sensor01;

void setup() {
  Serial.begin(115200);

  // Asignamos valores utilizando la notación "objeto.propiedad"
  // Por supuesto podríamos modificar estos valores en cualquier lugar del código
  sensor01.id = 4354;
  sensor01.seccion = 1;
  sensor01.descripcion = "Sensor vibraciones equipo 23";

  Serial.println("ESTRUCTURA");
  Serial.println("ID: " + String(sensor01.id));
  Serial.println("Seccion: " + String(sensor01.seccion));
  Serial.println("Descripcion: " + String(sensor01.descripcion));
}

void loop() {
  contador++;
  sensor01.lectura = contador;
  Serial.println("Lectura: " + String(sensor01.lectura));
  delay(1000);
}
