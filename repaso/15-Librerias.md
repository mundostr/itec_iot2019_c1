<h1><b>FUNDACION INSTITUTO TECNOLOGICO RAFAELA</b></h1>
<h2><b>Taller Arduino Adultos 2019</b></h2>

<h3>15- Librerías</h3>

Como ocurre en muchos lenguajes, el entorno de Arduino aprovecha la opción de librerías para extender la funcionalidad base del sistema. <b>Una librería no es más que un extracto de código encapsulado en un archivo separado, que puede ser incluido y reutilizado en otros</b>. Puede contener desde simples definiciones de variables e inicializaciones, a declaraciones de funciones, clases y otras.

El propio Arduino IDE contiene un set de librerías preinstaladas listas para utilizar, junto con un <a href="https://aprendiendoarduino.wordpress.com/2016/03/31/librerias-gestor-de-librerias/">Gestor</a> que nos permite buscar en repositorios online y agregar cualquier otra librería que podamos necesitar en nuestros proyectos. Si no fuese suficiente, podremos siempre agregar una de manera manual, por ejemplo extrayendo los contenidos desde un repositorio de Github al directorio de librerías de nuestra instalación Arduino. Se puede observar una lista de las librerías standard para Arduinos oficiales en el <a href="https://www.arduino.cc/en/Reference/Libraries">siguiente enlace</a>, por supuesto son solo algunas de las muchas disponibles en toda la comunidad. A través del manager incluido en el IDE, podremos buscar en los repositorios, o utilizar alternativamente algún servicio de índice de librerías de Arduino, como <a href="https://www.arduinolibraries.info/">https://www.arduinolibraries.info/</a>.

<p>&nbsp;</p>

<b>Incluyendo librerías</b>

La inclusión se realiza de manera muy sencilla, mediante la palabra reservada #include:

```
#include <nombreLibreria.h>
```

Mayormente el include utiliza un <i>archivo .h (header o cabecera de C)</i>, el cual a su vez puede "llamar" internamente a otros archivos si lo necesita, pero también puede insertarse directamente un archivo de código .c o .cpp por ejemplo. Al cargar la línea #include, si la librería se encuentra correctamente instalada en el sistema Arduino local, el IDE la identificará y cambiará el color del nombre a naranja, indicando que todo se encuentra listo para su uso; si en cambio la librería no está disponible, el nombre permanecerá en negro, y lógicamente no funcionará.

> En muchas oportunidades se puede ver la inclusión con esta sintaxis: #include "nombreLibreria.h", es decir, utilizando comillas en lugar de los signos menor/mayor. Si lo hacemos con comillas, el sistema buscará primero la librería en el mismo directorio del sketch, y luego irá a los directorios de librerías de la instalación de Arduino; si en cambio incluimos con los signos < y >, solo buscará en los directorios Arduino. Esta alternativa es útil cuando queremos probar una versión personalizada de una librería que ya tenemos instalada en nuestro sistema.

<p>&nbsp;</p>

<b>Alternativas portables</b>

Como sabemos, desde hace un tiempo el IDE oficial de Arduino puede instalarse de forma <i>portable</i>, para ello se descarga desde <a href="https://arduino.cc" target="_blank">arduino.cc</a> la versión del instalador en formato ZIP, se lo extrae en un directorio y se crea dentro un subdirectorio llamado <i>portable</i>. Para ejecutar se utiliza el arduino.exe ubicado en el directorio recién extraido, y a partir de allí el entorno trabajará todos sus contenidos dentro de <i>portable</i>. Podemos elegir guardar los sketches allí, cualquier librería o soporte de placas que instalemos también se agregará en el mismo directorio, con lo cual tendremos todo en un solo lugar.

Algunas veces pueden generarse conflictos de librerías entre distintos tipos de familias (por ejemplo entre ESP8266 y ESP32); con la alternativa portable es muy sencillo armar varios entornos de trabajo en la misma máquina, con paquetes de librerías independientes uno de otro.

<p>&nbsp;</p>

<b>Ejemplo de uso</b>

Supongamos que deseamos realizar el clásico ejercicio de parpadeo de led, pero aprovechando el control de tiempo que podemos hacer mediante la función <i>millis()</i>, en lugar de la función restrictiva <i>delay()</i>, y para simplificar la escritura, en lugar de llamar a <i>millis()</i> manualmente, aprovechamos una librería para hacerlo:

```
#include <elapsedMillis.h>

const byte PIN_LED = 2;
const byte INTERVALO_LED = 1000;

elapsedMillis timer01;

void setup() {
  pinMode(PIN_LED, OUTPUT);
}

void loop() {
  if (timer01 >= INTERVALO_LED) {
    digitalWrite(PIN_LED, !digitalRead(PIN_LED));
    timer01 = 0;
  }
}
```

Secuencia:

* <i>Inclusión de la librería</i> (elapsedMillis en este caso), la cual como mencionamos debe estar previamente instalada en nuestra estructura Arduino, de no estarlo podremos agregarla rápidamente mediante el Gestor.

* Creación de un <i>nuevo objeto de tipo elapsedMillis, llamado timer01</i>.

* Dentro del <i>loop()</i>, <i>uso del objeto timer01</i> para controlar cuándo ha transcurrido el intervalo de tiempo <i>INTERVALO_LED</i>, y el de la función <i>digitalWrite()</i> para cambiar el estado del led mediante la negación de su propia lectura.

* <i>Reseteo de timer01 a 0</i> para volver a esperar un nuevo intervalo.

<b>Vemos que de manera muy simple podemos incluir y reaprovechar la funcionalidad de una librería en nuestro código, lo cual lógicamente será de gran utilidad para agilizar y facilitar la escritura de proyectos</b>.

<p>&nbsp;</p>

<b>Atención!</b>

<b>Si bien es tentador comenzar a incluir gran cantidad de librerías en nuestro código, para encapsular y facilitar el uso de las distintas funcionalidades, debemos tener presente que esto conlleva un consumo extra de recursos de espacio, y muchas veces puede ralentizar también nuestro código, por ende es importante mantener coherencia en este aspecto, no abusando de inclusiones innecesarias que podemos resolver con escritura de código sencillo propio</b>.

Más info sobre el tema en <a href="https://aprendiendoarduino.wordpress.com/2016/11/16/librerias-arduino-2/">https://aprendiendoarduino.wordpress.com/2016/11/16/librerias-arduino-2/</a>.