void setup() {
  Serial.begin(115200);

  char cadenaFija[28] = "parte_fija_";
  // strcat(cadenaFija, cadenaRandom(16));

  Serial.println(cadenaRandom(16));
}

void loop() {
}

char* cadenaRandom(int longitud) {
  int nroRnd = 1;
  char cadena[4] = "";
  char caracteres[63] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

  nroRnd = random(62);
  cadena[0] = caracteres[nroRnd];
  cadena[1] = caracteres[nroRnd];
  cadena[2] = caracteres[nroRnd];

  return &cadena;
}
