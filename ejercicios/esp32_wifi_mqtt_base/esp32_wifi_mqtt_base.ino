#include <WiFi.h>
#include <PubSubClient.h>

const byte PIN_LED = 2;
const byte PIN_SENSOR = 23;

const char *REDWF = "APIOT";
const char *CLAVEWF = "arduino2019";
const char* SERVIDORMQTT = "broker.hivemq.com";
const int PUERTOMQTT = 1883;
const char* USUARIOMQTT = "";
const char* CLAVEMQTT = "";

WiFiClient cliente;
PubSubClient mqtt(cliente);

void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, LOW);
  
  Serial.println("SISTEMA INICIADO");
  Serial.println();

  conectarWiFi();
  conectarMqtt();
  enviarMqtt();
}

void loop() {
}

void conectarWiFi() {
  Serial.println("Conectando a red Wifi");
  WiFi.begin(REDWF, CLAVEWF);

  while (WiFi.status() != WL_CONNECTED) {}
  Serial.println("Wifi conectado");
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
}

void conectarMqtt() {
  mqtt.setServer(SERVIDORMQTT, PUERTOMQTT);

  while (!mqtt.connected()) {
    if (mqtt.connect("clienteESP32", USUARIOMQTT, CLAVEMQTT)) {
      digitalWrite(PIN_LED, HIGH);
      Serial.println("Mqtt conectado");
    } else {
      Serial.print("Mqtt: ERROR, ");
      Serial.println(mqtt.state());
      delay(3000);
    }
  }
}

void enviarMqtt() {
  String cadena = "{\"timestamp\": " + String(millis()) + ", \"valor\": 23 }";
  mqtt.publish("cperren/topico03", cadena.c_str(), true);
  Serial.println("Mensaje enviado");
}
