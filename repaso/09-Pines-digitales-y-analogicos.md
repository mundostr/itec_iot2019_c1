<h1><b>FUNDACION INSTITUTO TECNOLOGICO RAFAELA</b></h1>
<h2><b>Taller Arduino Adultos 2019</b></h2>

<h3>09- Pines digitales y analógicos</h3>

<img src="https://openwebinars.net/media/django-summernote/2015-01-31/12bddab0-3d93-4510-98ca-ef8a7410ed11.jpg" width="400">

Hasta el momento nos hemos manejado con pines digitales, es decir, controlando solo dos estados (encendido o apagado, on u off, high o low, 0 o 1, tiene o no tiene corriente), utilizando las bahías superiores de nuestra placa Arduino.

<b>De hecho un microcontrolador opera en la totalidad de sus pines de manera digital</b>, sin embargo <b>en oportunidades tendremos necesidad de medir magnitudes físicas que pueden asumir cualquier valor dentro de un rango</b>, aquí nos serán de utilidad los pines analógicos, que en el caso del Arduino UNO se ubican en una bahía en la parte inferior derecha.

<img src="https://openwebinars.net/media/django-summernote/2015-01-31/dea32eaf-5a37-4f8d-aeaf-4db538d71020.jpg" width="400">

Como mencionamos, internamente el microcontrolador opera de manera digital, entonces qué diferencia a los pines marcados con ADC?. Bien, dichos pines están conectados precisamente a lo que se denomina un <a href="https://aprendiendoarduino.wordpress.com/tag/adc/"><b>ADC (Analog Digital Converter) o Conversor Analógico Digital</b></a>, el cual se encarga de realizar una cuantificación para convertir el valor analógico en una codificación digital, y nos devuelve un número dentro de un rango, proporcional a la lectura analógica que está recibiendo.

<i>Este rango depende de la resolución del conversor, en el caso del Arduino UNO la resolución es de 10 bits (2 elevado a la 10 = 1024 valores diferentes), para el ESP32 disponemos de una resolución de 12 bits ADC, o sea 4096 posibles valores. Como veremos más adelante, esta resolución se puede ver afectada también por el rango de voltaje recibido en las entradas analógicas, y por supuesto, por la propia resolución de trabajo del elemento que estemos leyendo.

<p>&nbsp;</p>

<b>Realizando una lectura analógica</b>

Conectaremos el siguiente circuito, empleando el potenciómetro de 10k incluído en el kit, para intentar tener una lectura progresiva del valor del mismo.

<img src="http://www.mundostreaming.tv/itec/arduino/imgs/arduino_pot.png?rnd=2" width="400">

La conexión del pot es muy sencilla, los extremos van a 3V3 y GND (indistintamente), y el punto central cualquier pin que disponga de ADC. Intercambiando los extremos lograremos que el pot incremente su resistencia de forma horaria o antihoraria, es decir, solo invertiremos la lectura.

```
const byte PIN_POT = 36;
int lectura;

void setup() {
  Serial.begin(38400);
  pinMode(PIN_POT, INPUT);
}

void loop() {
  lectura = analogRead(PIN_POT);
  Serial.println(lectura);
  delay(50);
}
```

<b>Como vemos, solo declaramos una constante para hacer referencia al pin donde tenemos conectado el potenciómetro (en este caso el GPIO36), lo configuramos como entrada y lo leemos cíclicamente en el <i>loop()</i>, pero utilizando ahora la función <i>analogRead()</i> en lugar de <i>digitalRead()</i></b>.

Tras subir el código a la placa y abrir la consola serial, comenzaremos a ver una secuencia de las lecturas recibidas del pin, y al mover el potenciómetro, esta lectura cambiará entre 0 y 4095 (recordar que si deseamos cambiar el sentido de incremento del potenciómetro, solo invertimos 3V3 y GND en sus extremos).

<p>&nbsp;</p>

<b>Reorganizando los datos de lectura con <i>map()</i></b>

Sabemos que la lectura tomada del pin analógico, será proporcional al voltaje recibido, el que a su vez responderá por ejemplo en el caso de un sensor, al nivel de la magnitud que esté controlando (temperatura, presión, humedad, luminosidad, etc), pero a efectos de darle mayor utilidad en nuestro código, necesitaremos reconvertir esa lectura a un valor que resulte más cómodo para nosotros. Podremos hacerlo a través de la función <i>map()</i>, modificando el código anterior a lo siguiente:

```
const byte PIN_POT = 36;
int lectura;
int lecturaConvertida;

void setup() {
  Serial.begin(38400);
  pinMode(PIN_POT, INPUT);
}

void loop() {
  lectura = analogRead(PIN_POT);
  lecturaConvertida = map(lectura, 0, 4095, 0, 6);
  Serial.println(lecturaConvertida);
  delay(50);
}
```

<b>Los valores que veremos ahora en la consola serial, se encontrarán entre 0 y 6, "mapeados" en ese rango de acuerdo a la lectura original entre 0 y 4095. Si por ejemplo colocamos al pot en su posición media (estando entonces la lectura analógica alrededor de 2048), en la consola tendremos el valor 3</b>. <i>Atención!, ésto se verificará si estamos empleando un pot lineal, no así con uno de tipo logarítmico en el que la variación no es progresiva</i>.

> <i>Si bien la función map() de Arduino es muy cómoda, tiene la limitación de operar solamente con valores enteros</i>, con lo cual si queremos mapear el valor del pin a un rango de 1.5 a 3.2V por ej, no tendríamos una buena resolución para trabajar. <i>En ese caso deberemos escribir una función de mapeo personalizada que opere con float, o bien realizar el cálculo directamente de manera manual</i>.

Podremos agregar a nuestro código una función personalizada para emplear en lugar de la <i>map()</i> standard:

```
// Función alternativa al map() standard con decimales
float mapFloat(float x, float min_orig, float max_orig, float min_salida, float max_salida) {
  return (x - min_orig) * (max_salida - min_salida) / (max_orig - min_orig) + min_salida;
}
```