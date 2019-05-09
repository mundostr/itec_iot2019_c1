struct Tipo01 {
  int id;
  int total;
  String mensaje;
};

unsigned long contador;

Tipo01 informacion;

void setup() {
  Serial.begin(115200);
  informacion.id = 24;
  informacion.mensaje = "Un mensaje";
}

void loop() {
  contador++;
  informacion.total = contador;
  Serial.println(informacion.id);
  Serial.println(informacion.total);
  Serial.println(informacion.mensaje);
  Serial.println();
  delay(1000);
}
