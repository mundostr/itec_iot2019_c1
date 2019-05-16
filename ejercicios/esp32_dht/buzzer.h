const byte CANAL_PWM = 0;
const byte FREC_PWM = 2000;

void tono(byte tono) {
  ledcWrite(CANAL_PWM, tono);
}

void setearBuzzer() {
  ledcSetup(CANAL_PWM, FREC_PWM, 8);
  ledcAttachPin(PIN_BUZZER, CANAL_PWM);
  ledcWriteTone(CANAL_PWM, FREC_PWM);
  tono(0);
}
