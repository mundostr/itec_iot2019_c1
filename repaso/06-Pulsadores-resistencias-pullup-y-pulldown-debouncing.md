<h1><b>FUNDACION INSTITUTO TECNOLOGICO RAFAELA</b></h1>
<h2><b>Taller IOT 2019 C1</b></h2>

<h3>06- Pulsadores, resistencias pullup y pulldown, debouncing</h3>

<p>&nbsp;</p>

<b>Pulsadores</b>

<img src="https://www.picuino.com/_images/img-0095-c.jpg" width="500">

Otro elemento muy habitual en la mayoría de los circuitos, es el <b>pulsador</b>, ya sea para realizar un <b>reset, iniciar o finalizar una ejecución, como selector de opciones y otras</b>. Existen diferentes tipos de pulsadores, los de la foto superior son muy tradicionales, con 4 pines de sujeción. Más allá de tener 4 extremos, internamente éstos están conectados de a pares, es decir que <b>la secuencia se resume a conectar uno de los lados a voltaje o tierra según se desee, y el otro al pin digital de Arduino que se emplee como entrada</b>.

Los pulsadores pueden ser además del tipo <b>normalmente abierto o normalmente cerrado</b>. En el primer caso, el circuito tiende a mantenerse siempre abierto, y solo al ser presionado el botón del elemento flexor, se cierra; en el segundo caso, obviamente, lo opuesto. El funcionamiento será equivalente.

La conexión para el Arduino es muy sencilla:

<img src="http://mundostreaming.tv/itec/arduino/imgs/arduino_pulsador_simple.png#3" width="500">

Como podemos ver, una de las columnas se conecta en el ejemplo a VCC (3V3), y la otra al pin digital 5. Escribiendo el siguiente código, podemos tener una lectura continua del estado del pulsador:

```
#define PIN_BTN 5
int estadoBtn = 0;

void setup() {
  Serial.begin(38400);
  pinMode(PIN_BTN, INPUT);
}

void loop() {
  estadoBtn = digitalRead(PIN_BTN);
  Serial.println(estadoBtn);
}
```

En el código simplemente configuramos al pin 5 como entrada (INPUT), y dentro del loop() leemos continuamente su estado a través de digitalRead(), imprimiéndolo a consola. Un rápido razonamiento nos indica que al estar liberado el pulsador, el pin 5 estará en "0", y al estar pulsado pasará a "1", ya que se cerrará el circuito y recibirá un valor de corriente desde la salida de 3V3. Subamos este código al Arduino (CTRL + U) y veamos qué nos reporta la consola.

Podemos verificar que al mantener pulsado el botón, la lectura del pin se estabiliza y solo aparecen "1s", pero al liberarlo, la lectura comienza a fluctuar constantemente entre "0s" y "1s", lo cual desde ya no nos sirve, nos dará constantemente "falsos positivos".

> Este comportamiento es una situación habitual al operar con microcontroladores, lo que sucede es que al estar liberado el pulsador, el circuito queda abierto y por ende el pin 5 toma un estado "flotante", fluctuando de manera aleatoria.

<p>&nbsp;</p>

<b>Resistencia pull down</b>

<img src="http://mundostreaming.tv/itec/arduino/imgs/arduino_pulsador_pulldown.png#3" width="500">

<b>La solución al problema de fluctuación es muy sencilla, solo debemos agregar una conexión en el botón, utilizando una resistencia (de 10k habitualmente) a tierra, a esta resistencia la llamamos de pull down</b>.

<b>Atención!: ante la duda, desconectar siempre la alimentación del circuito, proceder a realizar los cambios de conexiones y luego realimentar</b>.

Si volvemos a ejecutar nuestro código y observamos la consola o el plotter serial, veremos ahora que con el botón "liberado", el pin se mantiene estable en "0", ya que está cerrando circuito a través de la resistencia de pulldown de 1k a tierra. Al presionar y cerrar el botón, la corriente circulará por el recorrido más directo desde 3V3 al pin 5, con lo cual la entrada del pin pasará a "1".

<p>&nbsp;</p>

<b>Resistencia pull up</b>

Podemos también invertir la situación, manteniendo el pin 5 siempre en "1", y pasándolo a "0" al presionar el botón.

<img src="http://mundostreaming.tv/itec/arduino/imgs/arduino_pulsador_pullup.png#3" width="500">

El funcionamiento es idéntico, pero ahora las condiciones se encuentran invertidas, o como decimos habitualmente, <b>"negadas"</b>. En la consola serial tendremos que observar continuamente "1s" con el botón liberado, y "0s" al presionarlo. <b>La resistencia, al estar conectada ahora a VCC, se denomina de pull up</b>.

> Ambas soluciones siguen el mismo concepto y son equivalentes, solo deberemos tener cuidado en nuestro código, al momento de consultar el estado del pin, de hacerlo en forma correcta, si opera con una resistencia de pull down, nos "preguntaremos" si el pin se encuentra en "1" para saber que ha sido pulsado; en el otro caso deberemos preguntarnos si se encuentra en "0".

<p>&nbsp;</p>

<b>Resistencias incorporadas</b>

La buena noticia es que los módulos <b>ESP32 incluyen tanto resistencias de pull up como de pull down internas en la mayoría de sus pines, las cuales podemos habilitar desde código</b>, de esta manera no tendremos necesidad de agregar resistencias externas, conectando solo el pulsador:

<img src="http://mundostreaming.tv/itec/arduino/imgs/arduino_pulsador_pullup_interna.png#3" width="500">

Para indicar que el pin 5 debe utilizar una resistencia de pull up interna, empleamos la constante INPUT_PULLUP:

```
#define PIN_BTN 5
int estadoBtn = 0;

void setup() {
  Serial.begin(38400);
  pinMode(PIN_BTN, INPUT_PULLUP); // utilizamos ahora la constante INPUT_PULLUP para habilitar la resistencia interna
}

void loop() {
  estadoBtn = digitalRead(PIN_BTN);

  if (estadoBtn == 0) { // Recordar ahora que la condición del pulsador se encuentra "negada"
    Serial.println("Pulsado");
  }
}
```

<b>Utilizando INPUT_PULLUP, aprovechamos la resistencia interna y el pin queda estabilizado a "1" cuando el pulsador se encuentra libre</b>, pasando a "0" cuando el pulsador es presionado. Solo debemos tener en cuenta al momento del <i>if</i> que verifica el estado del botón, de consultar por el estado "0" en lugar del "1". Si querríamos utilizar lógica directa, podríamos habilitarlo como INPUT_PULLDOWN.

Con esto, solucionamos la fluctuación del pin, uno de los problemas habituales al momento de utilizar pulsadores en microcontroladores. <b>Chequearemos ahora el 2do problema típico, llamado rebote (bouncing)</b>, con una corrección sencilla, si bien veremos más adelante que podemos manejar esto de forma más efectiva, utilizando directamente una librería para tal fin.

<b>Rebote (bouncing)</b>

El <b>rebote</b> es un inconveniente habitual en los pulsadores, originado por su accionamiento mecánico, el cual ocasiona falsas lecturas que pueden fácilmente "confundir" a nuestro código. Modifiquemos el ejemplo anterior para probarlo:

```
#define PIN_LED 2
#define PIN_BTN 5

int contador = 0;
int estadoBtn = 1; // Lo iniciamos en 1 porque utilizamos el INPUT_PULLUP, 0 si usáramos INPUT_PULLDOWN

void setup() {
  Serial.begin(38400);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BTN, INPUT_PULLUP);
}

void loop() {
  estadoBtn = digitalRead(PIN_BTN);

  if (estadoBtn == 0) { // Botón presionado, recordar el estado negado
    contador = contador + 1;
    Serial.print("Contador: ");
    Serial.println(contador);
  }

  if (contador == 5) {
    contador = 0;
    digitalWrite(PIN_LED, HIGH);
  }
}
```

Lo que hacemos aquí, es inicializar un contador e incrementarlo en 1 cada vez que se pulsa el botón. Cuando el contador llegue a 5, debe encenderse el led integrado en el pin 2. Sin embargo, al cargar el código y pulsar solo una vez el botón, vemos que el led enciende.

A qué se debe ésto?, bien, lo que para nosotros físicamente es una sola pulsación, a nivel eléctrico en la frecuencia de operación del microcontrolador, es un tiempo prolongado en el cual toma reiteradas lecturas de pulsación, mientras el botón está moviéndose de su estado abierto a su posición final presionada.

Para solucionarlo, implementamos este código de debouncing sumamente sencillo:

```
#define PIN_LED 2
#define PIN_BTN 5

int contador = 0;
int estadoBtn = 1;
int estadoActualBtn = estadoBtn;

void setup() {
  Serial.begin(38400);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BTN, INPUT_PULLUP);
}

void loop() {
  estadoBtn = digitalRead(PIN_BTN);

  if (estadoBtn == 0 && estadoActualBtn == 1) { // Botón presionado, recordar estado negado
    contador = contador + 1;
    Serial.print("Contador: ");
    Serial.println(contador);
  }

  estadoActualBtn = estadoBtn;
  delay(30);

  if (contador == 5) {
    contador = 0;
    digitalWrite(PIN_LED, HIGH);
  }
}
```

Aquí agregamos una nueva variable estadoActualBtn, que inicia con el valor 1, al igual que estadoBtn. <b>La primera vez que presionemos el botón, estadoBtn (que guarda el estado del pin 5) pasará a "0", y estadoActualBtn estará en 1, con lo cual se cumplirá la condición del <i>if</i> y se ejecutará su código interno, aumentándose el contador en 1. De inmediato a través de estadoActualBtn = estadoBtn;, estadoActualBtn pasará a "0", con lo cual en las sucesivas lecturas que se producirán mientras estemos presionando el botón hasta llegar a su posición física final, el <i>if</i> ya no se cumplirá</b>.

Este sencillo truco, junto a un delay de 30 ms, nos brinda suficiente estabilidad para leer y contar correctamente las pulsaciones del botón. Por supuesto, ni bien liberamos el botón, la próxima lectura de estadoBtn volverá a "1" (recordar que estamos utilizando INPUT_PULLUP = negado), y estadoActualBtn también lo hará, ya que lo estamos asignando debajo del <i>if</i>, quedando listo para captar nuevamente de forma correcta la próxima pulsación.

Como veremos más adelante, esta es una forma funcional pero precaria de control, perfectamente útil para entender los conceptos de trabajo, pero que en códigos de producción reemplazaremos habitualmente por otras alternativas.