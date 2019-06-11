/*
  Control de tareas alternativo con Task Scheduller, opera con ESP8266, ESP32 y STM32.
  https://github.com/arkhipenko/TaskScheduler
*/

#include <TaskScheduler.h>

const byte LED = 2;

void cbTarea1();
void cbTarea2();
void cbTarea3();

Scheduler tareas;
Task tarea1(2000, 5, &cbTarea1);
Task tarea2(250, TASK_FOREVER, &cbTarea2);
Task tarea3(5000, 2, &cbTarea3);

void cbTarea1() {
  if (tarea1.isFirstIteration()) {
    Serial.println("INICIO");
  }

  Serial.println("Ejecuta tarea1");

  if (tarea1.isLastIteration()) {
    tarea2.setInterval(1000);
    tareas.addTask(tarea3);
    tarea3.enable();
    Serial.println("Fin tarea1, Inicio tarea3, cambio tarea2");
  }
}

void cbTarea2() {
  digitalWrite(LED, !digitalRead(LED));
}

void cbTarea3() {
  if (tarea3.isLastIteration()) {
    Serial.println("Ejecuta tarea3");
    Serial.println("FINALIZA");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  tareas.init();
  tareas.addTask(tarea1);
  tareas.addTask(tarea2);
  tarea1.enable();
  tarea2.enable();

  Serial.println("SISTEMA ACTIVO");
}

void loop() {
  tareas.execute();
}
