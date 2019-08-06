#include <WiFi.h>
#include <OneWire.h>
#include <PubSubClient.h>
#include <TaskScheduler.h>
#include <Adafruit_NeoPixel.h>
#include <DallasTemperature.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define BOTtoken "token_bot_telegram"
String        CHAT_ID = "id_chat_telegram";
const byte    MULTILED = 19;
const byte    PIN_SENSOR = 23;
const byte    LED = 2;
const byte    ALARMA_TEMP_MAX = 25;
const byte    ALARMA_TEMP_MIN = 10;
const char    *WIFI_SSID = "ITEC - Publica";
const char    *WIFI_CLAVE = "";
const char*   SERVIDORMQTT = "broker.shiftr.io";
const int     PUERTOMQTT = 1883;
const char*   USUARIOMQTT = "usuario_mqtt";
const char*   CLAVEMQTT = "clave_mqtt";

float   TEMP_MAX = -1000;
float   TEMP_MIN = 1000;
float   SUMA = 0;
float   PROMEDIO = 0;
float   datos[10];
int     i = 0; //contador de datos
String  texto;
byte    CANT_MUE = 10;
int     Bot_mtbs = 1000; //mean time between scan messages
long    Bot_lasttime;   //last time messages' scan has been done
bool    Start = false;

void cbleerSensor();
void cbsubeArchivo();

OneWire oneWire(PIN_SENSOR);
DallasTemperature sensor(&oneWire);

WiFiClient cliente0;
PubSubClient mqtt(cliente0);

WiFiClientSecure cliente1;
UniversalTelegramBot bot(BOTtoken, cliente1);

Scheduler tareas;
Task leerSensor(1000, TASK_FOREVER, &cbleerSensor);

enum colores { ROJO, VERDE, AZUL, AMARILLO, MAGENTA };
Adafruit_NeoPixel ledM = Adafruit_NeoPixel(1, MULTILED, NEO_GRB + NEO_KHZ800);

void cbleerSensor() {//---------------------------------                  LEER SENSOR       ----------------------------------
  sensor.requestTemperatures();
  datos[i] = sensor.getTempCByIndex(0);
  SUMA = SUMA + datos[i];
  cambiarColorLedM(0, AMARILLO);
  delay(100);
  //mqtt.publish("gbernasconi/sensor01", cadena.c_str(), true);

  if (datos[i] < TEMP_MIN) {
    TEMP_MIN = datos[i];
  }
  if (datos[i] > TEMP_MAX) {
    TEMP_MAX = datos[i];
  }

  if (datos[i] > ALARMA_TEMP_MAX) {
    String cadena = " TEMP ALTA: " + String(datos[i]) + " !!!";
    Serial.println("");
    Serial.print(cadena);
    enviarMensaje(CHAT_ID, cadena);
    Serial.println(datos[i]);
    i = 0;
  }
  if (datos[i] < ALARMA_TEMP_MIN) {
    Serial.println("");
    Serial.print("Notificar TEMP BAJA: ");
    Serial.println(datos[i]);
    i = 0;
  }
  i++;
  if (i == CANT_MUE) {
    PROMEDIO = SUMA / CANT_MUE;
    SUMA = 0;
    i = 0;
  }
}

void grabaArchivo() {
  for (int k = 0; i < CANT_MUE; k++) {
    datos[k] = 0;
  }
}

void suscribir() {
  mqtt.setCallback(cbMensajes);
  mqtt.subscribe("gbernasconi/LED01");
  mqtt.subscribe("gbernasconi/LED02");
}

void cbMensajes(char* topico, byte* payload, unsigned int length) { //------------------------------       MENSAJES       ------------------------------------------
  Serial.println(topico);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  if (String(topico) == "gbernasconi/LED01") {
    cambiarColorLedM(0, AMARILLO);
  }
  if (String(topico) == "gbernasconi/LED02") {
    cambiarColorLedM(0, MAGENTA);
  }
}

void handleNewMessages(int numNewMessages) { //---------------------------------       HANDLE NEW MENSSGES       ----------------------------------
  Serial.println("Nuevo Mensaje");
  Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++) {
    
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Guest";

    if (text == "/test") {
      bot.sendChatAction(CHAT_ID, "escribir");
      delay(4000);
      enviarMensaje(CHAT_ID, "¿Viste el mensaje de acción?");
    }
    if (text == "/start") {
      texto = "Bienvenido a Universal Arduino Telegram Bot library, " + from_name + ".\n";
      texto += "Ejemplo de chatBot.\n\n";
      texto += "/test : para realizar pruebas\n";
      enviarMensaje(CHAT_ID, texto);
    }
    else if (text == "/lucesOn") {
      texto = "Luces encendidas";
      digitalWrite(LED, HIGH);
      enviarMensaje(CHAT_ID, texto);
    }
    else if (text == "/lucesOff") {
      texto = "Luces apagadas";
      digitalWrite(LED, LOW);
      enviarMensaje(CHAT_ID, texto);
    }
    else if (text == "/temp") {
      texto = "Valor de la Temp:" + String(sensor.getTempCByIndex(0)) + " °C";
      enviarMensaje(CHAT_ID, texto);
      Serial.println(texto);
      
      texto = "  MAX: " + String(TEMP_MAX) + "  MIN: " + String(TEMP_MIN) + "  PROM: " + String(PROMEDIO);
      enviarMensaje(CHAT_ID, texto);
      Serial.println(texto);
    }
  }
}


void setup() {                      //-----------------------------------------------       SETUP       -----------------------------------------------
  pinMode(LED, OUTPUT);
  ledM.begin();
  Serial.begin(115200);
  Serial.println("SISTEMA INICIADO - ROJO");
  Serial.println();
  cambiarColorLedM(0, ROJO);

  conectarWiFi();
  conectarMqtt();
  //suscribir();
  enviarMensaje(CHAT_ID, "Mensaje de prueba: " + String(millis()));
  
  //https://api.telegram.org/bot<token>/getUpdates    ---> poner en <token> el de nuestro bot
  //https://api.telegram.org/bot865388920:AAGLwP7V5JvVhh9I18Efb0t15aE7UIDsXNY/getUpdates
  
  tareas.init();
  tareas.addTask(leerSensor);
  leerSensor.enable();
}

void loop() {                           //-----------------------------------------------       LOOP       -----------------------------------------------
  cambiarColorLedM(0, MAGENTA);
  //mqtt.loop();
  tareas.execute();
  if (millis() > Bot_lasttime + Bot_mtbs)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    Bot_lasttime = millis();
  }
}

void conectarWiFi() {
  Serial.println("Conectando a red Wifi");
  WiFi.begin(WIFI_SSID, WIFI_CLAVE);
  while (WiFi.status() != WL_CONNECTED) {}
  Serial.println("Wifi conectado - VERDE");
  Serial.println();
  cambiarColorLedM(0, VERDE);
  Serial.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
}

void conectarMqtt() {
  mqtt.setServer(SERVIDORMQTT, PUERTOMQTT);
  while (!mqtt.connected()) {
    if (mqtt.connect("clienteESP32", USUARIOMQTT, CLAVEMQTT)) {
      Serial.println("Mqtt conectado - AZUL");
      Serial.println();
      cambiarColorLedM(0, AZUL);
      delay(1000);
    }
    else {
      Serial.print("Mqtt: ERROR, ");
      Serial.println(mqtt.state());
      delay(3000);
    }
  }
}

void enviarMqtt(float temp) {
  String cadena = " { \"T\": " + String(temp) + " }";
  Serial.println(cadena);
  mqtt.publish("gbernasconi/sensor01", cadena.c_str(), true);
  Serial.println("Mensaje enviado");
}

void cambiarColorLedM(byte led, colores color) {
  ledM.clear();
  switch (color) {
    case ROJO:
      ledM.setPixelColor(led, 0, 255, 0);
      break;
    case VERDE:
      ledM.setPixelColor(led, 255, 0, 0);
      break;
    case AZUL:
      ledM.setPixelColor(led, 0, 0, 255);
      break;
    case AMARILLO:
      ledM.setPixelColor(led, 255, 255, 0);
      break;
    case MAGENTA:
      ledM.setPixelColor(led, 0, 255, 255);
      break;
  }
  ledM.show();
}
void enviarMensaje(String idDestino, String mensaje) {
  if (bot.sendMessage(idDestino, mensaje, "")) {
    Serial.println("Mensaje enviado");
  } else {
    Serial.println("ERROR al enviar mensaje");
  }
}
