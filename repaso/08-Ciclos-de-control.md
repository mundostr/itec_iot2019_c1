<h1><b>FUNDACION INSTITUTO TECNOLOGICO RAFAELA</b></h1>
<h2><b>Taller IOT 2019 C1</b></h2>

<h3>08- Ciclos de control</h3>

<p>&nbsp;</p>

<b>loop()</b>

Partiendo de la estructura básica de nuestro código, podemos ver un ciclo implícito:

```
void setup() {
}

void loop() {
}
```

Recordemos que ambas funciones deben encontrarse siempre en el código Arduino que utilicemos, setup() será ejecutada solo una vez al inicio, y lo que coloquemos dentro de <b>loop() se ejecutará secuencialmente de manera indefinida</b> mientras la placa permanezca energizada. <b>loop() por ende, es un ciclo infinito</b>.

En oportunidades necesitaremos generar ciclos infinitos, y en otras, ciclos que se ejecuten solo una determinada cantidad de veces.

<b>Ciclo for</b>

<b>El ciclo o bucle <i>for()</i> nos permite precisamente ejecutar comandos una cierta cantidad de veces</b>, por ejemplo para incrementar una variable o recorrer una matriz. La sintaxis es:

```
int contador;

for (byte i = 0; i < 4; i++) {
  contador = contador + 3;
}
```

Como vemos, definimos una variable índice (i) que en este caso es de tipo byte (0 a 255), ya que solo la usaremos en el rango 0 a < 4, es decir, a medida que se ejecute el <i>for()</i> tomará los valores 0, 1, 2 y 3, y contador se irá incrementando de a 3 mientras i < 4. En el siguiente ciclo ya no se cumplirá la condición i < 4, y el <i>for()</i> finalizará.

En el ejemplo de arriba, la variable índice (i, o cualquier nombre que deseemos colocar) solo fue definida para cumplir con la declaración, pero no la hemos aplicado en nada dentro. Sin embargo en muchos casos será de utilidad, como por ejemplo al momento de recorrer una matriz:

```
int acumulador;
int matriz[4] = {22, 6, 1, 2};

for (byte i = 0; i < 4; i++) {
  acumulador = acumulador + matriz[i];
}
```

<b>El índice (i) nos permite obtener en cada ciclo el valor del item específico de la matriz (recordar que el primer item tiene siempre el índice 0, no 1)</b>.

<p>&nbsp;</p>

<b>Ciclo o bucle while()</b>

A diferencia de <i>for()</i>, <b>while() ejecuta un ciclo indefinidamente, mientras se cumpla la condición especificada</b>, tan pronto dicha condición deje de cumplirse, el ciclo finalizará. Si deseamos reescribir el contador de arriba con <i>while()</i>, lo hacemos de la siguiente manera:

```
int ciclo = 0;
int contador = 0;

while (ciclo < 4) {
  ciclo = ciclo + 1;
  contador = contador + 3; 
}
```

Vemos que en esta situación los códigos son equivalentes, podríamos activar el ciclo del contador tanto con <i>for()</i> como con <i>while()</i> sin problemas. En otras situaciones, la opción del <i>while()</i> es muy cómoda, como el caso de aguardar el pulsado de un botón para iniciar una secuencia:

```
#define PIN_PULSADOR 7

void setup() {
  Serial.begin(38400);
  pinMode(PIN_PULSADOR, INPUT_PULLUP);

  Serial.println("Aguardando pulsacion de boton...");
  
  while(digitalRead(PIN_PULSADOR) == HIGH) {
    delay(50);
    // Simplemente mientras leamos un "1" o HIGH en el pin del pulsador, quedaremos aquí en espera
    // Ni bien leamos un "0" o LOW, la condición del while() será falsa y el ciclo indefinido se interrumpirá,
    // al interrumpirse terminará de ejecutarse el setup() y se pasará al loop()
    // Recordar que se encuentra negado al utilizar INPUT_PULLUP,
    // entonces el pulsador "libre" estará en "1" y presionado en "0"
  }

  Serial.println("Boton pulsado, en 5 segs iniciamos secuencia.");
  delay(5000);
}

void loop() {
  Serial.println("Ejecutando loop()");
  // Aquí ejecutamos el código cíclico, pero el loop() no comenzará hasta tanto deje de cumplirse la condición del while()
}
```

> Atención!: no debemos olvidar que en estos casos estamos realizando una tarea a la vez, como veremos más adelante, cuando sea necesario manejar varias tareas de forma simultánea dentro del <i>loop()</i>, deberemos tener mucho cuidado en el empleo de <i>delay() o while()</i>, ya que interrumpirán por completo el resto de las operaciones hasta tanto finalicen.