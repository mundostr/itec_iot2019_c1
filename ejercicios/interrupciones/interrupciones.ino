/*
  Manejo BASE de interrupciones con ESP32
  Habitual en programación de micros, utilizable por ejemplo en captura de sensores de rpm, etc.
*/

const byte PULSADOR = 23;
unsigned long timerAntirrebote = 0;
volatile boolean estado = LOW;

/*
  Función ISR (Interrupt Service Routine), IRAM_ATTR indica que el código compilado de la rutina se guarda
  en memoria RAM interna del micro, no en Flash.
  1- Se debe mantener con la menor cantidad posible de código, para una ejecución muy rápida.
  2- NO se pueden pasar argumentos.
  3- NO se puede utilizar millis(), ya que dicha función emplea interrupciones, por lo tanto no incrementa dentro de una ISR.
  4- NO se puede utilizar delay(), idem caso anterior
  5- Para cualquier ajuste de tiempo, se debe emplear delayMicroseconds()
*/
void IRAM_ATTR control() {
  estado = HIGH;
}

void setup() {
  Serial.begin(115200);
  // Activamos la resistencia de pulldown interna, por lo tanto el pulsador deberá conectar a 3V3
  pinMode(PULSADOR, INPUT_PULLDOWN);
  // Activamos una interrupción para el pin del pulsador
  attachInterrupt(digitalPinToInterrupt(PULSADOR), control, RISING);
}

void loop() {
  if (estado) {
    Serial.println(estado);
    delay(250);
    estado = LOW;
  }
}
