#include "driver/adc.h"
#include "esp_adc_cal.h"

uint32_t lectura;

void setup() {
  Serial.begin(1000000);
  for (int i = 0; i < 100; i++) {
    lectura = adc1_get_raw(ADC1_CHANNEL_0);
    // uint32_t lecturaV = esp_adc_cal_raw_to_voltage(lectura, adc_chars);
    Serial.println(lectura);
    delay(50);
  }
}

void loop() {
}
