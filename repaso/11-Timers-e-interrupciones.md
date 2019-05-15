<h1><b>FUNDACION INSTITUTO TECNOLOGICO RAFAELA</b></h1>
<h2><b>Taller Arduino Adultos 2019</b></h2>

<h3>11- Temporizadores (timers e interrupciones)</h3>

Sabemos que podemos efectuar un control de tiempo básico mediante llamadas a la función <i>delay()</i> en milisegundos. Si bien es válido, <b>esta solución implica que durante los momentos en los cuales se ejecute la espera, el microcontrolador no podrá atender nada más</b>, solo quedará al aguardo de cumplirse ese plazo para continuar:

```
void loop() {
  digitalWrite(2, !digitalRead(2));
  delay(500);
}
```

Con este simple código podemos parpadear infinitamente al led incorporado en el pin 2, y si es solo esa tarea la que realizaremos, no existe problema, pero si necesitamos por ejemplo atender el parpadeo y simultáneamente quedar atentos a la pulsación de un botón, no será posible, el sistema simplemente hará caso omiso de cualquier pulsación que realicemos.

<p>&nbsp;</p>

<b>La opción millis()</b>

<b>Una de las formas de solucionar ésto, es utilizar la función <i>millis()</i>, la cual devuelve el número de milisegundos transcurridos desde que se comenzó a ejecutar el programa actual</b>. Esta función obtiene la información de un timer interno que se incrementa constantemente, hasta llegar a un <i>overflow</i> en aprox. 50 días, comenzando nuevamente desde 0, por ende si en nuestra aplicación necesitamos dejar operando desatendido el micro por más de 50 días, tendremos que contemplar en el código este retorno a 0, para el resto de los casos ese límite será mucho más que suficiente.

Si chequeamos constantemente el retorno de <i>millis()</i> y lo evaluamos dentro de una condición, podremos llevar un control de tiempo preciso para ejecutar procesos a intervalos definidos:

```
const long INTERVALO = 60000;

unsigned long timer1 = 0;

void setup() {
}

void loop() {
  if (millis() - timer1 >= INTERVALO) {
    // Ejecutamos el código que deseemos y por último actualizamos el timer
    timer1 = millis();
  }
}
```

Podemos ver que hemos definido una variable <i>timer1</i> de tipo <i>unsigned long</i> para llevar un registro del último momento en el cual se ejecutó el intervalo. En el condicional, restamos al valor de tiempo actual devuelto por millis() el que tenemos almacenado en timer1, y lo comparamos con nuestro INTERVALO, cuando esa resta iguale o supere a INTERVALO, significará que ese período de tiempo habrá transcurrido, la condición será <i>verdadera</i> y por lo tanto se ejecutará lo que esté dentro del <i>if()</i>. Allí haremos lo que necesitemos, y por último actualizaremos <i>timer1</i> al valor actual de <i>millis()</i>, para mantener la frecuencia en funcionamiento.

En el ejemplo, INTERVALO está fijado en 60000 (milisegundos = 60 segs = 1 min), es decir, queremos ejecutar un determinado código, una vez por minuto.

Si tomamos un ciclo al azar para analizarlo, supongamos a los 10 segundos de iniciado el programa:

* <i>millis()</i> = 10000
* <i>timer1</i> = 0
* INTERVALO = 60000
* Condición if: 10000 - 0 >= 60000: false

Antes del primer minuto, la condición se evaluará constantemente a falso. Veamos la situación al llegar al primer minuto:

* <i>millis()</i> = 60000
* <i>timer</i> = 0
* INTERVALO = 60000
* Condición if: 60000 - 0 >= 60000: true

Ahora la condición se cumple y por lo tanto se ingresa a ejecutar el codigo contenido en el <i>if</i>. Al final de este código, se actualiza <i>timer1</i> al valor de <i>millis()</i>, esto es MUY importante para mantener la secuencia en funcionamiento.

Si nos fijamos entonces qué sucede al minuto y medio de iniciado el código:

* <i>millis()</i> = 90000
* <i>timer1</i> = 60000 (ya no es 0, se actualizó en el último ingreso al <i>if</i>)
* INTERVALO = 60000
* Condición if: 90000 - 60000 >= 60000: false

En cada condición validada como verdadera, se actualizará <i>timer1</i> al valor actual de <i>millis()</i>, en saltos de 60000 milisegundos en este ejemplo (o por supuesto, cualquier valor que coloquemos en INTERVALO). De allí en más la condición volverá a false hasta que transcurra nuevamente el plazo de INTERVALO.

Si suponemos que ya estamos en el minuto 2 luego de iniciar el código:

* <i>millis()</i> = 120000
* <i>timer1</i> = 60000
* INTERVALO = 60000
* Condición if: 120000 - 60000 >= 60000: true

Otra vez la condición valida como true, se vuelve a ejecutar su código interno y <i>timer</i> se actualiza, continuando de esa manera la frecuencia sin problemas.

<p>&nbsp;</p>

<b>millis() mediante librerías</b>

<b>ellapsedMillis</b>

Si no queremos plantear las condiciones de <i>millis()</i> manualmente, podemos aprovechar alguna librería escrita a tal efecto, como elapsedMillis:

```
#include <elapsedMillis.h>

bool estadoLed = LOW;
const byte PIN_LED = 2;
const byte INTERVALO_LED = 100;

elapsedMillis timer01;

void setup() {
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  if (timer01 >= INTERVALO_LED) {
    estadoLed = !estadoLed;
    digitalWrite(PIN_LED, estadoLed);
    timer01 = 0;
  }
}
```

Al incluir la librería <i>elapsedMillis</i>, se vuelve disponible en nuestro código una clase del mismo nombre, con la cual podemos definir un objeto (línea <i>elapsedMillis timer01;</i>) para controlar los intervalos de tiempo. Una vez disponible el objeto, simplemente lo comparamos con la constante de intervalo que hayamos definido (<i>INTERVALO_LED</i>) para saber cuánto tiempo ha transcurrido, y ejecutamos dentro de la condición el código que necesitemos, sin olvidar resetear a 0 (<i>timer01 = 0;</i>) para comenzar a controlar el próximo intervalo.

<p>&nbsp;</p>

<b>Gestión de tareas alternativa en ESP32 con Ticker</b>

<p>&nbsp;</p>

Desde hace un tiempo, la distribución oficial del módulo ESP32 para el entorno de Arduino, incluye la librería Ticker, que nos permite manejar la gestión de tareas frecuentes de forma muy intuitiva.

```
#include <Ticker.h>

const byte LED = 2;
const byte SENSOR = 17;

// Definimos un par de objetos para control de tareas
Ticker ctrlLed;
Ticker ctrlSensor;

void alternarLed() {
  digitalWrite(LED, !digitalRead(LED));
}

void leerSensor() {
  // Acá colocamos la secuencia de lectura y asignamos las variables que correspondan
}

void setup() {
  pinMode(LED, OUTPUT);
  ctrlLed.attach_ms(100, leerSensor);
  ctrlLed.attach_ms(1000, alternarLed);
}

void loop() {
}
```

Mediante <i>Ticker</i>, podemos definir la cantidad de objetos de control que necesitemos, y a través de los métodos <i>attach</i> o <i>attach_ms</i>, indicar cada cuántos segundos o milisegundos debemos ejecutar el contenido de una determinada función. Como puede verse, el <i>loop()</i> standard queda vacío, es el propio sistema esp_timer interno del ESP32 el que mantiene las tareas en operación. Alternativamente, si queremos ejecutar una determinada tarea solo UNA vez, utilizamos los métodos <i>once</i> o <i>once_ms</i> en la asignación del setup().

> <b>Importante!: si bien existe también una librería Ticker para Arduinos convencionales, se trata de proyectos diferentes, la que vemos es una implementación específica para micros ESP32.

<p>&nbsp;</p>

<b>Interrupciones de hardware</b>

Hasta el momento nos hemos manejado con tareas periódicas, es decir, ejecutadas a intervalos regulares de tiempo, controlados manualmente mediante <i>millis()</i> o a través de alguna librería. Si por ejemplo necesitábamos estar atentos al cambio de estado de un botón, definíamos un intervalo razonable (50 ms por ejemplo), y chequeábamos cada vez que transcurría ese tiempo, si el estado había cambiado.

El método es funcional, no tiene nada de malo, sin embargo presenta algunas desventajas cuando lo aplicamos a <i>eventos</i> que no sabemos en qué momento se producirán: un botón de inicio / parada de emergencia por ej, se puede pulsar de inmediato o no, de cualquier manera con este método estaremos chequeando repetidamente cada 100 ms (este mecanismo de consulta repetida de entradas se suele llamar "poll" en inglés). La desventaja principal es el mayor consumo de procesamiento y energía.

<p>&nbsp;</p>

> Aquí surge la opción de <b>interrupciones de hardware</b>, otra variante en microcontroladores para atender justamente a <i>eventos</i> no programados. Las interrupciones hw asocian una función definida por el usuario (ISR = Interrupt Service Routine) a un <i>evento</i> de cambio de estado en un pin físico, con prioridad TOTAL, es decir, ni bien se sucede el evento, el micro deriva la ejecución al contenido de la función ISR relacionada, y tan pronto ésta termina, retorna al flujo principal, en el lugar exacto donde lo había interrumpido, y continúa desde allí (lógicamente todo esto se sucede en microsegundos).

<img src="https://cdn-learn.adafruit.com/assets/assets/000/021/334/medium640/components_interrupt.png?1416523011" width="400">

En realidad, internamente un micro utiliza de forma constante interrupciones (por ej para la transmisión serie, la comunicación I2C, el manejo de delay() y millis(), o el reseteo de la placa luego de grabar un nuevo código). El uso de ellas en nuestro código no es obligatorio, en especial con programas sencillos, pero se vuelve muy efectivo en programas más avanzados.

Como mencionamos, una <i>interrupción</i> está ligada a un <i>evento</i> de cambio de estado en un pin determinado. <b>Así como en el caso de un Arduino UNO, solo los pines digitales 2 y 3 son utilizables para interrupciones por HW, en un ESP32 la mayor parte de sus pines se pueden emplear para este cometido (revisar imagen interrupciones en pinouts)</b>.

Una vez que definimos el pin a utilizar, debemos indicar el evento por el cual se "disparará" la interrupción, y la función a ejecutar, veamos entonces cómo escribimos ese código:

```
const byte SENSOR = 17; 
volatile int contador;

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR procesar() {
  portENTER_CRITICAL(&mux);
  contador++;
  portEXIT_CRITICAL(&mux);
}

void setup() {
  pinMode(SENSOR, INPUT);
  attachInterrupt(digitalPinToInterrupt(SENSOR), procesar, FALLING);
}

void loop() {
}
```

Vemos varios puntos interesantes:

* la llamada a <i>attachInterrupt</i> para definir la interrupción.
* el uso de <i>digitalPinToInterrupt</i> para indicar cuál es el pin digital que deseamos utilizar.
* la indicación de la función ISR a la que se derivará la ejecución de código, en este caso <i>procesar()</i>.
* la indicación del evento que nos interesa monitorear sobre ese pin, en el ejemplo, FALLING.

Vamos a explicar un poco más los eventos disponibles para ser capturados en interrupciones con ESP32:

* <b>LOW</b>: se disparará tan pronto como el pin entre en un estado bajo (0).
* <b>CHANGE</b>: se disparará cada vez que el pin cambie de estado (sea de 0 a 1 o de 1 a 0).
* <b>RISING</b>: se disparará tan pronto como el pin comience a cambiar de 0 a 1.
* <b>FALLING</b>: se disparará tan pronto como el pin comience a cambiar de 1 a 0.
* <b>HIGH</b>: se disparará tan pronto como el pin entre en un estado alto (1).
(atención!, el evento HIGH NO puede utilizarse en muchos Arduinos habituales, excepsiones son el Due, el Zero o las placas MKR1000. En el caso de los ESP32, sí podemos aplicarlo).

<p>&nbsp;</p>

> De esta manera, la línea:
>
> attachInterrupt(digitalPinToInterrupt(SENSOR), procesar, FALLING);
>
> se traduce como "habilitar interrupción en el GPIO17, para ejecutar la función <i>procesar()</i> tan pronto como el estado del pin comience a caer de 1 a 0" (en este caso el sensor en el pin está operando con lógica negada).

> <b>Importante!: al diseñar una función ISR, tengamos en mente que la misma debe consumir el menor tiempo de ejecución posible, por lo general lo vamos a utilizar para cambiar de estado a variables booleanas, incrementar contadores y demás, luego en el flujo principal realizaremos otras tareas debido a esos cambios. NO es aconsejable colocar dentro, operaciones que consuman tiempo alto como comunicación serial o I2C por ejemplo, mientras más concisa, mejor.

<p>&nbsp;</p>

En este caso nos estamos refiriendo a <i>interrupciones</i> por hardware, ya que las mismas responden a eventos de pines, es decir, cambios de estado en los mismos. Veremos más adelante que también podemos usar interrupciones por <i>software</i>, las que responden a instrucciones, como un watchdog por ejemplo.