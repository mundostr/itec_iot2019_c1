<h1><b>FUNDACION INSTITUTO TECNOLOGICO RAFAELA</b></h1>
<h2><b>Taller IOT 2019 C1</b></h2>

<h3>04- Constantes, variables, tipos de datos, estructuras de control</h3>

<p>&nbsp;</p>

<b>Instalando lo necesario y repasando los primeros conceptos de programación</b>

Como ya hemos mencionado, la gran <b>versatilidad y comodidad de Arduino</b>, radica en la posibilidad de contar en <b>una única placa con los distintos elementos necesarios para grabar y probar código en microcontroladores, con una interfaz directa que permite enlazar fácilmente dicha placa con una PC</b>, notebook, netbook o celular. Por supuesto, esto <b>debe complementarse con un IDE (Entorno Integrado de Desarrollo) cómodo y accesible</b>, tanto para el programador avanzado como para el principiante, este es el IDE oficial de Arduino, descargable gratuitamente desde su página:

<b><a href="https://www.arduino.cc/en/Main/Software">https://www.arduino.cc/en/Main/Software</a></b>

La instalación del IDE es muy sencilla -tanto en Linux, como Windows y Mac- siguiendo los pasos del asistente el programa estará listo para utilizar en cuestión de un par de minutos, incluso puede descargarse una versión alternativa que no requiere privilegios para su ejecución y puede instalarse para ser utilizada de forma portable, lo cual es realmente cómodo. Cuenta con total soporte de lenguaje en español.

Una pantalla inicial típica del programa, es la siguiente:

<img src="https://support.content.office.net/es-es/media/e8c360e1-2b32-45db-b9d7-d43abc86af2f.png" width="900">

Este IDE no es más que un entorno simplificado, orientado específicamente a las necesidades de Arduino, el lenguaje de fondo utilizado en la programación es C y C++, pero como dijimos, bajo un entorno simplificado, que permite también tener cómodo acceso a las herramientas de líneas de comando para compilación y carga de código, pudiendo realizar los diferentes pasos de manera práctica a través de íconos y teclas de acceso rápido.

<p>&nbsp;</p>

<b>Estructura básica de un sketch de Arduino</b>

`void setup() { }`

`void loop() { }`

Antes de comenzar a programar nuestro Arduino, debemos entender algunos conceptos primarios de funcionamiento dentro de su estructura de programación.

Todo sketch Arduino contiene <b>2 bloques ensenciales: setup() y loop()</b>, el código contenido dentro de <b>setup() se ejecutará solo una vez al inicio</b>, y el que se encuentre dentro de <b>loop() se ejecutará indefinidamente</b> mientras el micro permanezca energizado.

Esencialmente utilizaremos sintaxis de C y C++ para escribir nuestro código, si bien será en un entorno simplificado, orientado a la comodidad de la programación Arduino. El <i>código fuente</i> que escribamos en el IDE, se guardará con extensión <i>.ino</i>, y al momento de ser subido a la placa, pasará por un proceso de análisis sintáctico, luego preprocesamiento, compilación, ensamblaje y linkeo, que terminará generando un archivo binario listo para subir al microcontrolador.

Si se desean mayores detalles sobre la secuencia de compilación, se puede visitar el siguiente enlace:
<a href="https://www.deviceplus.com/how-tos/arduino-guide/arduino-preprocessor-directives-tutorial/">https://www.deviceplus.com/how-tos/arduino-guide/arduino-preprocessor-directives-tutorial/</a>

<p>&nbsp;</p>

<b>Comenzando con los elementos de código</b>

<b>Constantes</b>

Las constantes, tal cual su nombre lo indica, <b>permiten definir un valor que no se alterará durante toda la ejecución del programa</b>. Existen 2 formas de notación:

`#define NOMBRE_CONSTANTE VALOR (ej: #define CONST01 3)`

`const tipo nombreVariable = valor (ej: const int pinLed = 3)`

El método #define es más antiguo y ampliamente difundido, aunque técnicamente lo ideal es la 2da alternativa, mediante const, si bien en muchos casos a nivel práctico será indistinto aplicar uno u otro. El hecho de escribir el nombre de la constante completamente en mayúsculas, se utiliza como convención.

Nuestro primer código será el clásico encendido de un led, y para ello aprenderemos ya algunas funciones clásicas dentro del entorno Arduino:

```
#define PIN_LED 2
// también podríamos utilizar const int PIN_LED = 2;

void setup() {
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  digitalWrite(PIN_LED, HIGH);
  delay(1000);

  digitalWrite(PIN_LED, LOW);
  delay(1000);
}
```

En la primer línea utilizamos el método <i>#define</i> para definir una constante llamada PIN_LED, con el valor 2.
La segunda línea comenzando con doble barra (//) es un comentario, para recordar la manera menos habitual pero ideal técnicamente de definir constantes.

Dentro del setup() (recordar que este código se ejecuta solo una vez al iniciar), utilizamos la función pinMode() para configurar el pin identificado por PIN_LED como salida (aprovechando otra constante predefinida, OUTPUT).

En el loop (recordar que este código se ejecuta indefinidamente), aplicamos la función digitalWrite() para escribir un alto (HIGH) en el pin PIN_LED, luego la función delay() para aguardar 1 segundo (1000 milisegundos), repetir digitalWrite() pero escribiendo unbajo en el pin (LOW) y finalmente otro delay de 1s. Ejecutada esta línea, el loop cerrará el ciclo y comenzará nuevamente.

Cable aclarar que en las placas Arduino Uno, disponemos de un led integrado, conectado al pin digital 13, es por esta razón que para este primer ejemplo, no hemos necesitado realizar ninguna conexión externa.

Tenemos nuestro código listo, cómo lo cargamos a la placa?:

* <b>Archivo -> Salvar (tecla rápida CTRL + S)</b>: nos brinda el diálogo de sistema para nombrar y almacenar nuestro código en disco. El IDE de Arduino creará siempre un directorio (carpeta) con el mismo nombre que hemos elegido, y pondrá dentro <b>el archivo, el cual tendrá la extensión .ino</b>.

* <b>Programa -> Verificar/Compilar (CTRL + R)</b>: con este comando iniciamos la secuencia de etapas que incluyen una verificación de sintaxis de nuestro código, el enlace de las distintas librerías y la compilación final del programa, para chequear que todo se encuentre en orden.

* <b>Programa -> Subir (CTRL + U)</b>: este comando incluye los pasos de la opción Verificar/Compilar, y si todo es validado, carga finalmente el código binario en el microcontrolador de nuestra placa, tras ello el Arduino reiniciará y comenzará automáticamente a ejecutar dicho código.

Si hemos seguido los pasos correctamente, tras elegir <i>Programa -> Subir</i>, veremos en la consola de la zona inferior de pantalla, cómo se ejecuta una secuencia de comandos de verificación, enlace y compilación, para subir en última instancia el código final al Arduino, dándonos el mensaje <i>Subido</i> tras completar, con la indicación del espacio utilizado en el micro y demás detalles.

Tendremos que habituarnos a prestar atención a esta consola inferior, aquí el IDE nos detallará también los problemas en caso de encontrar errores de sintaxis, conexión y otros.

<b>Nuestro primer código Arduino se encuentra cargado en el micro y funcionando!</b>, el Led integrado en la placa (identificado con la letra L), debe parpadear indefinidamente, encendido durante 1 segundo, apagado durante 1 segundo.

> Ejercicio!: tomar el protoboard y repetir el uso de este primer código, pero encendiendo un led externo, conectado al pin digital 5. Recordar la necesidad de agregar una resistencia de 220 ohm al led, para su funcionamiento correcto con alimentación de 5V.

<img src="http://mundostreaming.tv/itec/arduino/imgs/arduino_ej_led_externo.png" width="500">

Aquí más detalles de cómo calcular la resistencia en función de las características del led, buena lectura para aprendizaje:

<a href="https://hetpro-store.com/TUTORIALES/resistencia-de-led/">Cálculo de resistencias para leds</a>

<p>&nbsp;</p>

<b>Variables</b>

Otro elemento primario de cualquier lenguaje. Mediante una variable, procedemos a reservar un espacio de memoria en el cual almacenar un valor determinado de un tipo específico de dato, y la identificamos con un nombre arbitrario. Obviamente, las variables sí podrán modificar su valor a lo largo de la ejecución del programa. Vamos con el código:

```
#define PIN_LED 2
int frecParpadeo = 10; // definimos la variable frecParpadeo, de tipo entero (int) y le asignamos el valor 10

void setup() {
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  digitalWrite(PIN_LED, HIGH);
  delay(frecParpadeo);

  digitalWrite(PIN_LED, LOW);
  delay(frecParpadeo);

  frecParpadeo = frecParpadeo + 10;
}
```

Modificando el código previo, incorporamos la definición de una variable entera (int frecParpadeo = 10); con la sentencia frecParpadeo = frecParpadeo + 10, incrementamos la variable en cada ciclo del loop, y ahora en las sentencias delay, en lugar de colocar un valor fijo, empleamos dicha variable. Esta es una simple demostración de cómo definir, inicializar y modificar una variable, el led comenzará su parpadeo con una frecuencia muy alta (ya que frecParpadeo inicia en 10 => 10 milisegundos), e irá paulatinamente parpadeando más y más despacio, a medida que el valor de frecParpadeo crezca.

> En los nombres de variables se suele usar la convención llamada lowerCamelCase, donde la primer letra de cada palabra en el nombre, se coloca con mayúsculas (excepto la primera), pero también podría escribirse completamente en minúsculas, o si se desea separar las palabras, con guiones bajos, ejemplos: frecuenciaDeParpadeo, frecuenciadeparpadeo, frecuencia_de_parpadeo

<p>&nbsp;</p>

<b>Tipos de datos</b>

Al definir variables, funciones y métodos, debemos declarar siempre el tipo de dato al cual hacemos referencia. Entre los más utilizados podemos listar:

* <b>void</b>: vacío, lo empleamos en funciones que no deben retornar ningún valor
* <b>boolean</b>: true o false
* <b>char</b>: caracter
* <b>byte</b>: entero de 0 a 255 (equivale a <b>uint8_t</b> de C)
* <b>word</b>: entero de 0 a 65535 (equivale a <b>uint16_t</b> de C)
* <b>int</b>: entero de -32768 a 32767 (equivale a <b>short</b>, <b>int16_t</b> de C)
* <b>long</b>: de -2147483648 a 2147483647 (equivale a <b>int32_t</b> de C)
* <b>unsigned long</b>: de 0 to 4,294,967,295 (equivale a <b>uint32_t</b> de C) 
* <b>float</b>: decimal de 32 bit (7 dígitos decimales de precisión)
* <b>double</b>: decimal de 64 bit (15 dígitos decimales de precisión)
* <b>String</b>: cadena de caracteres

<i>Modificador <b>unsigned</b></i>: como vemos, hay tipos de datos que solo permiten operar con valores positivos, y otros que lo hacen tanto con positivos como negativos (int, long, float, double). Puede suceder que necesitemos definir una variable de tipo <i>long</i> por ejemplo, ya que almacenaremos un indicador de tiempo transcurrido que puede tornarse muy grande, pero como sabemos el tiempo nunca asumirá un valor negativo; en este caso agregaremos delante de <i>long</i> el modificador <i>unsigned</i>, para indicarle al compilador que solo estaremos haciendo uso del rango positivo en el que opera ese tipo de dato, de esta forma evitaremos reservar sin necesidad, bloques de memoria para el rango negativo que jamás estaremos utilizando.

<p>&nbsp;</p>

<b>Estructuras de control: if</b>

Agregaremos ahora la primer estructura de control, el <i>if</i>, que nos permitirá verificar si una determinada <i>condición</i> se cumple o no. Solo si dicha condición se verifica, se ejecutará el código contenido en la estructura.

```
#define PIN_LED 2
int frecParpadeo = 10;

void setup() {
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  digitalWrite(PIN_LED, HIGH);
  delay(frecParpadeo);

  digitalWrite(PIN_LED, LOW);
  delay(frecParpadeo);

  frecParpadeo = frecParpadeo + 25;

  if (frecParpadeo >= 500) {
    frecParpadeo = 10;
  }
}
```

Vemos un código muy similar al anterior, pero al final del loop() principal, hemos agregado una condición if() que chequea si la variable frecParpadeo es mayor o igual a 500; <b>solo</b> si se verifica dicha condición, retorna el valor de frecParpadeo a 10. De esta forma, el led iniciará parpadeando a una frecuencia alta, y paulatinamente irá desacelerando, pero al llegar a una frecuencia de 500 (o el valor inmediatamente superior según el número que utilicemos para incrementar frecParpadeo), comenzará nuevamente a parpadear de forma enérgica.

Dentro del if, para generar nuestra condición, hemos utilizado un <i>operador de comparación</i>, más específicamente el >= (mayor o igual), es decir que la condición será verdadera si frecParpadeo es igual o mayor a 500.

Operadores aritméticos:

* =, igual
* +, suma
* -, resta
* *, multiplicación
* /, división
* %, módulo

Operadores booleanos (que debemos utilizar para elaborar las condiciones):

* ==, igual a
* !=, distinto de
* <, menor que
* \>, mayor que
* <=, menor o igual que
* \>=, mayor o igual que

<p>&nbsp;</p>

<b>Estructuras de control: if else</b>

Como mencionamos, el código contenido entre las llaves de la estructura <i>if</i>, solo se ejecutará si se cumple la condición indicada, pero habrá casos en los cuales necesitaremos ejecutar un determinado código si se cumple, u otro si no se cumple, de forma excluyente:

```
const byte PIN_SWITCH = 3;

void setup() {
  pinMode(PIN_SWITCH, INPUT_PULLUP);
  Serial.begin(38400);

  if (!digitalRead(PIN_SWITCH)) {
    Serial.println("Switch activado");
  } else {
    Serial.println("Switch desactivado");
  }
}

void loop() {
}
```

Podemos ver en esta fracción muy simple de código, que según la lectura del switch conectado en el pin 3, mostraremos una u otra notificación en consola serie.

<p>&nbsp;</p>

<b>Operador ternario</b>

El operador ternario permite expresar una condición mediante una sintaxis alternativa más compacta, lo cual para ciertos casos puede resultar muy cómodo, por ejemplo:

````
const byte POT = A0;
bool rangoAlto = false;

void setup() {
  Serial.begin(38400);
  pinMode(POT, INPUT);
}

void loop() {
  digitalRead(POT) <= 512 ? rangoAlto = false : rangoAlto = true;
  Serial.println("El rango es alto: " + String(rangoAlto));
}
````

La línea que nos interesa es:

````
digitalRead(POT) <= 512 ? rangoAlto = false : rangoAlto = true;
````

que es simplemente una expresión compacta de:

````
if (digitalRead(POT) <= 512) {
  rangoAlto = false;
} else {
  rangoAlto = true;
}
````

<p>&nbsp;</p>

En el siguiente enlace, se podrá descargar un cheatsheet imprimible con un resumen de estos operadores y otros conceptos básicos, muy útil para el repaso:

<a href="http://mundostreaming.tv/itec/arduino/cheatsheet_arduino_01.pdf">http://mundostreaming.tv/itec/arduino/cheatsheet_arduino_01.pdf</a>

Mayores detalles en la referencia de lenguaje oficial:

<a href="https://www.arduino.cc/reference/en/">https://www.arduino.cc/reference/en/</a>

<p>&nbsp;</p>

<b>Switch case</b>

La estructura switch, es otra opción de control de flujo para el programa, permitiendo evaluar diferentes valores de una variable y ejecutar solo el código específico para cada caso.

````
switch (comando) {
  case 'iniciar':
    // Ejecuta código de inicio
    break;
  case 'detener':
    // Ejecuta código de cierre
    break;
  case 'pausar':
    // Ejecuta código de pausa
    break;
  default:
    // Ejecuta código solo si ninguna de las opciones anteriores se verifica
}
````

Podemos ver que cada opción del <i>case</i>, cierra con un <i>break</i>, lo cual permite "saltar" directamente al cierre del <i>switch</i> si esa condición se ha verificado, pues en ese caso ninguna de las siguientes se verificará, no tendría sentido seguir evaluando las demás.

También vemos la opción </i>default</i> ubicada al final de la lista. Esta es otra característica cómoda del <i>switch</i> que posibilita ejecutar un código por defecto, es decir, un código que solo se ejecutará si ninguna de las opciones anteriores se verifica.

En el ejemplo, si los comandos permitidos en nuestro sistema son "iniciar", "detener" y "pausar", en el default generemos un aviso de error, sin importar cuál ha sido el comando ingresado, solo nos interesa saber que no ha sido ninguno de los 3 permitidos.

<p>&nbsp;</p>

<b>Compilación condicional</b>

Otro mecanismo muy útil en nuestros programas, es la evaluación de constantes previo a la compilación, para determinar si un bloque de código es incluído o no en el binario final. Veamos el siguiente ejemplo:

````
#define AJUSTAR

const byte SENSOR = A0; // equivalente a pin 14 en Arduino UNO
const float K = 3.64;
float calculo;
int lectura;

void setup() {
  pinMode(SENSOR, INPUT);
}

void loop() {
  lectura = analogRead(SENSOR);
  
  #ifdef AJUSTAR
    calculo = lectura * K;
  #else
    calculo = lectura;
  #endif
}
````

Si <i>#define AJUSTAR</i> se encuentra al inicio del código, es decir, si se definió la constante AJUSTAR, en el <i>loop()</i>, luego del <i>analogRead()</i>, solo se compilará <i>calculo = lectura * K</i>; si en cambio la constante no está definida (si comentamos la línea por ejemplo), automáticamente al momento de compilar, ese código será solamente <i>calculo = lectura</i>.

Como vemos, se trata de un simple <i>if else</i> al que ya estamos habituados, con la diferencia que dicha evaluación no se realiza en tiempo de ejecución sino de compilación, incluyendo solo uno u otro código en el binario definitivo. Esto es algo muy cómodo, que gran cantidad de librerías y otros códigos distribuidos utilizan, para permitir seleccionar un tipo de sensor por ejemplo, o realizar otro tipo de seteos.

La lista de condicionales para compilación, incluye:

* #if: evalúa una condición.
* #ifdef: evalúa si una constante se encuentra definida.
* #ifndef: evalúa si una constante no se encuentra definida.
* #else: sino habitual.
* #elif: sino si habitual.
* #endif: cierre de condición que siempre debemos colocar.