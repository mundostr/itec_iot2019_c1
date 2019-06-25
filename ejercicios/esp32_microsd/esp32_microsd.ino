/*
  Ejemplo de trabajo con módulo SPI lector de tarjetas SD
*/

// FS y SD son librerías instaladas de forma predeterminada en el paquete ESP32
#include <FS.h>
#include <SD.h>
// Lo mismo la SPI, que nos permite manejar dispositivos que operen con ese protocolo
#include <SPI.h>

const byte PIN_SD = 5;
String datos;

void setup() {
  Serial.begin(115200);

  inicializarSD();
  crear(SD, "/prueba01.txt", "Contenido de prueba");
  agregar(SD, "/prueba01.txt", "Segundo contenido de prueba");
}

void loop() {
}

void inicializarSD() {
  // Intentamos inicializar el lector, si no es posible, aguardamos y reintentamos.
  if (!SD.begin(PIN_SD)) {
    Serial.println("ERROR de lector SD.");
    delay(5000);
    inicializarSD();
  }
  revisarTarjeta();
}

void revisarTarjeta() {
  // Intentamos acceder a la tarjeta y notificamos si no está presente.
  byte tipoSD = SD.cardType();
  if (tipoSD == CARD_NONE) {
    Serial.println("No se detecta tarjeta.");
    delay(5000);
    revisarTarjeta();
  }
}

void crear(fs::FS &fs, const char * ruta, const char * contenido) {
  // Abrimos el archivo en modo ESCRITURA
  File archivo = fs.open(ruta, FILE_WRITE);
  if (!archivo) {
    Serial.println("No se puede abrir el archivo para escritura");
    return;
  }
  // Colocamos el contenido pasado a la función
  if (archivo.print(contenido)) {
    Serial.println("Archivo creado y actualizado");
  } else {
    Serial.println("ERROR al escribir");
  }
  // Cerramos el control del archivo
  archivo.close();
}

void agregar(fs::FS &fs, const char * ruta, const char * contenido) {
  // Abrimos el archivo en modo AGREGADO
  File archivo = fs.open(ruta, FILE_APPEND);
  if (!archivo) {
    Serial.println("No se puede abrir el archivo para agregado");
    return;
  }
  // Cargamos el contenido pasado a la función
  if (archivo.print(contenido)) {
    Serial.println("Archivo actualizado");
  } else {
    Serial.println("ERROR al actualizar");
  }
  // Cerramos el control del archivo
  archivo.close();
}
