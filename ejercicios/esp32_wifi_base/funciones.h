const char* REDWF = "APIOT";
const char* CLAVE = "arduino2019";

String verTipoEnc(wifi_auth_mode_t tipo) {
  switch (tipo) {
    case (WIFI_AUTH_OPEN):
      return "Abierta";
    case (WIFI_AUTH_WEP):
      return "WEP";
    case (WIFI_AUTH_WPA_PSK):
      return "WPA_PSK";
    case (WIFI_AUTH_WPA2_PSK):
      return "WPA2_PSK";
    case (WIFI_AUTH_WPA_WPA2_PSK):
      return "WPA_WPA2_PSK";
    case (WIFI_AUTH_WPA2_ENTERPRISE):
      return "WPA2_ENTERPRISE";
  }
}

void buscarRedes() {
  int redesDisponibles = WiFi.scanNetworks();

  if (redesDisponibles > 0) {
    Serial.println("Redes WF disponibles:");
    Serial.println();
    for (byte c = 0; c < redesDisponibles; c++) {
      Serial.println(String(WiFi.SSID(c)) + " (" + String(WiFi.RSSI(c)) + "), " + verTipoEnc(WiFi.encryptionType(c)));
    }
  } else {
    Serial.println("No hay redes WF disponibles en el area en este momento");
    while (1);
  }
}

void conectarWiFi() {
  WiFi.begin(REDWF, CLAVE);

  Serial.println("Conectando a " + String(REDWF));
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("OK! ");
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
}
