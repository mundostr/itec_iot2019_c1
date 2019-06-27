/*
  https://github.com/me-no-dev/arduino-esp32fs-plugin
  https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/
  https://randomnerdtutorials.com/esp32-web-server-spiffs-spi-flash-file-system/

  Ejemplo de uso del sistema SPIFFS para almacenar y gestionar archivos en el propio ESP32
  Para comenzar a utilizarlo -como cualquier sistema de archivos- es necesario LA PRIMERA VEZ,
  definir y formatear una partición, lo cual se realiza siguiendo estos pasos:

  1) Crear un sketch nuevo y guardarlo.
  2) Presionar CTRL + K para abrir el directorio de ese sketch
  3) Crear en ese lugar un subdirectorio llamado "data" (sin las comillas)
  4) Colocar dentro de data cualquier archivo que se quiera almacenar en el SPIFFS, por ejemplo un index.html
  5) Ir a Herramientas -> ESP32 Sketch Data Upload para cargar. Este paso iniciará el formateo y
  preparará el sistema para futuras cargas.
*/

#include <SPIFFS.h>

void listarDir(char *dir) {
  static int archivos;
  archivos = 0;

  File raiz = SPIFFS.open(dir);
  File archivo = raiz.openNextFile();

  Serial.println("Listado de " + (String)dir);
  while (archivo) {
    archivos++;
    Serial.print("Archivo: ");
    Serial.println(archivo.name());
    archivo = raiz.openNextFile();
  }

  if (archivos == 0) {
    Serial.println("No hay archivos");
  }
}

void leerArchivo(char *arc) {
  Serial.println("Lectura de " + (String)arc);

  File archivo = SPIFFS.open(arc);
  if (!archivo) {
    Serial.println("Error al abrir el archivo para lectura");
    return;
  }

  Serial.println("Contenido:");
  while (archivo.available()) {
    Serial.write(archivo.read());
  }
  archivo.close();
}

boolean guardarArchivo(char *arc, char *contenido) {
  bool todoOk;
  File archivo = SPIFFS.open(arc, "w");
  if (archivo.print(contenido)) {
    todoOk = true;
  } else {
    todoOk = false;
  }
  archivo.close();
  return todoOk;
}

boolean actualizarArchivo(char *arc, char *contenido) {
  bool todoOk;
  File archivo = SPIFFS.open(arc, "a");
  if (archivo.print(contenido)) {
    todoOk = true;
  } else {
    todoOk = false;
  }
  archivo.close();
  return todoOk;
}

void setup() {
  Serial.begin(115200);

  if (!SPIFFS.begin(false)) { // true para forzar formato si falla el montaje
    Serial.println("ERROR al montar SPIFFS");
    return;
  }
  Serial.println("SPIFFS montado (" + String(SPIFFS.usedBytes()) + " bytes usados)");

  listarDir("/");
  
  // leerArchivo("/prueba.txt");
  
  //  if (guardarArchivo("/prueba.txt", "Contenido de prueba")) {
  //    Serial.println("Archivo actualizado");
  //  } else {
  //    Serial.println("ERROR al actualizar el archivo");
  //  }
}

void loop() {
}
