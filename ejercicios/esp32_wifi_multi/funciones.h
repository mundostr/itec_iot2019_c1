WiFiMulti wf;

void configurarWiFi() {
  WiFi.mode(WIFI_STA);
  wf.addAP("cualquierRed", "clave");
  wf.addAP("APIOT", "arduino2019");
}

void conectarWiFi() {
  Serial.println("Conectando a red WiFi");
  while (wf.run() != WL_CONNECTED) {}
  Serial.println("OK!, conectado a " + String(WiFi.SSID()));
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
}
