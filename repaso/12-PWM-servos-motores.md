<h1><b>FUNDACION INSTITUTO TECNOLOGICO RAFAELA</b></h1>
<h2><b>Taller Arduino Adultos 2019</b></h2>

<h3>12- PWM (Modulación de ancho de pulso = Pulse width modulation). Servos y otros motores.</h3>

<p>&nbsp;</p>

Hasta el momento nos hemos manejado de forma digital, a través de las funciones de alto nivel <i>digitalRead()</i> y <i>digitalWrite()</i> que nos provee el entorno de Arduino. Con ellas podemos fácilmente leer o escribir a un pin de manera binaria (1 o 0, true o false, HIGH o LOW).

Hemos revisado entradas analógicas mediante <i>analogRead()</i>, función que nos brinda la posibilidad de utilizar el conversor analógico digital (ADC) de nuestra placa de desarrollo, para leer una magnitud dentro de un rango, de acuerdo al voltaje de referencia. Esa lectura en el caso del ESP, dada la resolución predeterminada de 12 bits para ADC, variará entre 0 y 4095 en la salida de la función.

Esto en lo referente a ENTRADAS, pero cómo podemos manejarnos cuando necesitamos una SALIDA que no sea booleana, sino variable dentro de un rango?. En ese caso podemos utilizar un DAC (Digital Analog Conversor) si nuestra placa cuenta con dicho soporte; o bien emplear una técnica ampliamente standarizada, <b>el PWM</b>, sobre cualquiera de los pines con soporte para ello.

<p>&nbsp;</p>

> <b>PWM (Pulse width modulation) es una técnica para modificar el ciclo de trabajo de una señal periódica (cuadrada o senoidal) a efectos de controlar la energía de salida o simplemente enviar información, es decir, <i>se trata de un proceso digital para representar una salida analógica</i></b>.

<img src="https://upload.wikimedia.org/wikipedia/commons/4/49/Pwm_5steps.gif" width="400">

Con esta simple gráfica, apreciamos que <b>en PWM tanto el voltaje como la frecuencia de la señal permanecen CONSTANTES, lo que se modifica es el pulso de trabajo, es decir, cuánto tiempo la señal se encuentra en ALTO y cuánto en BAJO durante cada ciclo</b>.

<p>&nbsp;</p>

En nuestras placas podemos fácilmente trabajar con esta técnica usando la función <i>analogWrite()</i>, aplicada sobre los pines 3, 5, 6, 9, 10 y 11, que son los habilitados de forma predeterminada para PWM. Decimos de forma predeterminada, porque trabajando a bajo nivel, podríamos también aplicar PWM manualmente empleando cualquier pin, pero a efectos prácticos nos mantendremos bajo la comodidad de <i>analogWrite()</i>, siendo más que suficiente para una gran cantidad de proyectos.

Vayamos ahora con un ejemplo aplicando un simple led, pero que en lugar de encenderse al 100% o apagarse, pueda modular su intensidad de luz, esta modulación dependerá del valor recibido de un potenciómetro.

<img src="https://www.mundostreaming.tv/itec/arduino/imgs/arduino_pot_led.png?rnd=1035" width="600">

````
const byte LED = 5;
const byte POT = A0;
int lectura, mapeo;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(POT, INPUT);
}

void loop() {
  lectura = analogRead(POT);
  mapeo = map(lectura, 0, 1023, 0, 255);
  analogWrite(LED, mapeo);
  delay(50);
}
````

Vemos que <i>analogWrite()</i>, aplicada a un pin PWM (5 en este caso), genera directamente la señal PWM hacia el led, permitiendo modular su brillo en lugar de solo encenderlo y apagarlo. El empleo de <i>map()</i> simplifica en una sola línea el mapeo del valor recibido de A0 (entre 0 y 1023) al rango 0 a 255 que requiere la salida PWM, siendo 0 equivalente a un pulso continuo de 0v y 255 a un pulso continuo de 5V (o el voltaje que se utilice como referencia). De esa forma, si por ej. analogWrite() se usa con un valor de 128, estaremos definiendo un pulso PWM (o duty cycle) del 50%, es decir, durante cada ciclo, la señal permanecerá la mitad del tiempo encendida, y la mitad apagada.

Podremos variar con rapidez y facilidad ese duty cycle entre 0 y 100 (0 a 255 dentro de la función) y controlar de esa forma la salida. Claramente no es de gran utilidad manejar la intensidad de un led, pero empleando los mismos conceptos manejaremos con gran precisión diferentes tipos de dispositivos, como servos y otros tipos de motores, los que sí resultarán de sumo provecho.

Más info de PWM en <a href="https://aprendiendoarduino.wordpress.com/2017/10/22/entradas-y-salidas-analogicas-arduino-pwm/">Aprendiendo Arduino</a>.

<p>&nbsp;</p>

<b>PWM y Servos</b>

<img src="http://www.superrobotica.com/Images/servos1.jpg" width="400">

Tanto en Arduino como en otras plataformas y robótica en general, los servos son elementos muy utilizados. En su gran mayoría se aprovechan servos de Aeromodelismo, si bien existen algunos modelos específicos para robótica. Un servo de este tipo consiste esencialmente de un pequeño motor DC, un tren de engranajes, un circuito controlador y un potenciómetro, todo compactado dentro de una caja única, lo cual le confiere robustez y practicidad.

El potenciómetro se encuentra conectado al engranaje principal del servo (el que porta el brazo), y por lo tanto se mueve solidario a él. El pequeño circuito controlador, utiliza este potenciómetro como encoder, chequeando continuamente su posición para saber si debe girar o detener el motor, y en qué sentido. De esa manera puede tener un control eficiente de la ubicación del brazo del servo dentro del rango de recorrido.

La función esencial de un servo es mover y retener la posición de su brazo dentro de un rango de rotación determinado, en lugar de girar de forma continua como un motor convencional. Este rango habitual es de <b>180 grados</b>, la gran mayoría de los servos comerciales se encuentran en esta categoría. No obstante existen también <i>servos de giro múltiple</i> donde el eje es capaz de rotar 2 o 3 vueltas entre topes, y <i>servos de rotación continua</i> que giran de forma permanente, resultando muy prácticos para impulsar robots por ejemplo. En el enlace de abajo pueden ver una breve descripción sobre el tema, y la forma simple de convertir cualquier servo standard en rotación continua, mediante el método de fijado o reemplazo del potenciómetro por resistencias, pot externo o preset:

<a href="http://www.ardumania.es/trucar-servo-a-rotacion-continua/">http://www.ardumania.es/trucar-servo-a-rotacion-continua/</a>

Existe una relación lineal entre el ancho de pulso aplicado y la posición del brazo del servo:

<img src="https://che-charls-electroall.webnode.es/_files/200000192-c5d25c6cd1/pwm%20servo-4.JPG" width="400">

<b>El rango standard de pulso PWM para servos es de 1000 a 2000 us (microsegundos)</b>, es decir, 1 a 2 ms (milisegundos), si bien en la práctica estos límites no son exactos. Variando este pulso, variaremos la ubicación del brazo respecto a su centro, así un pulso de 1000 us (o menos) moverá el brazo completamente a izquierda (0 grados, antihorario); un pulso de 2000 us (o más) lo hará completamente a la derecha (180 grados, horario); uno de 1500 us lo centrará (90 grados), y así linealmente para cualquier valor en el rango.

<p>&nbsp;</p>

<b>El standard de conexión</b>

Existe un standard de conexión ampliamente difundido en el ambito de los servos, que respeta el siguiente esquema:

<img src="https://www.mundostreaming.tv/itec/arduino/imgs/arduino_servo.png" width="600">

La gran mayoría de los servos operan con límite de voltaje de 5 o 5.5V, podemos apreciar que el +5 siempre se ubica en el centro de la ficha de conexión (rojo), siendo uno de los extremos GND (marrón o negro) y el otro señal PWM (naranja o blanco). Como mencionamos, esta disposición y codificación de colores se utiliza ampliamente en todo el mundo, y permite conectar los servos con facilidad y a prueba de cortos. Si se invirtieran GND y señal, lógicamente el servo no funcionaría pero tampoco se dañaría su electrónica.

> <b>Mucho cuidado!</b>: si bien el rango de operación de 5V permite conectar este tipo de servos de forma directa a un pin Arduino, y el driver integrado protege al microcontrolador de cualquier corriente residual, esto SOLO es recomendable con pequeños servos de bajo consumo (aquellos de 9 grs o similares). Si se requiere trabajar con servos de mayor tamaño y torque, utilizar siempre una fuente externa para alimentarlos, conectar únicamente a Arduino el GND compartido y la señal PWM.

<p>&nbsp;</p>

<b>Manejando servos con comodidad mediante la librería Servo</b>

Si bien tampoco resulta difícil escribir código PWM de forma manual, es sumamente práctico manejarlo mediante una librería. <b>Servo</b> es la librería standard del entorno Arduino para este fin, normalmente se encuentra incluida en la instalación del Arduino IDE. Para manejar un servo, bastará con un código como el siguiente:

````
#include <Servo.h>

const byte PIN_SERVO = 9;

Servo motor01;

void setup() {
  motor01.attach(PIN_SERVO);
  motor01.write(0);
  delay(3000);
  motor01.write(180);
  delay(3000);
  motor01.write(90);
}

void loop() {
}
````

Vemos que la librería nos expone un objeto <i>Servo</i> que podemos utilizar para declarar nuestro propio objeto (motor01 en este caso) y mediante él, manejar el servo sin problemas. Relacionamos el pin PWM a utilizar mediante el método <i>attach()</i>, y luego con <i>write()</i> indicamos directamente en grados la posición deseada del brazo.

Si lo deseamos, podemos reemplazar <i>write</i> por <i>writeMicroseconds()</i> y posicionar utilizando el rango original en us (microsegundos). Así, si quisiéramos ubicar el brazo del servo a la mitad de su recorrido, escribiríamos:

``
motor01.writeMicroseconds(1500);
``

> Recordar que el rango de 1000 a 2000 us es solo nominal, en la práctica existen diferencias en los extremos, por ende si se requiere un movimiento muy preciso que utilice todo el rango físico de rotación, se deberán verificar primero estos límites y ajustar el código en consecuencia.

<p>&nbsp;</p>

<b>Controlando motores DC (corriente continua)</b>

<b>La técnica de PWM se utiliza ampliamente no solo para el control de servos, sino también para motores DC, brushless y otros</b>. Un pequeño motor DC como el incluido en el kit (caja de engranajes amarilla), se puede manejar cómodamente por PWM, agregando tan solo un transistor de tipo NPN como driver, o bien cualquier driver comercial como el L293 o adaptadores basados en él.

<b>El transistor es una solución muy simple, permitiendo no solo encender y detener el motor, sino también controlar su régimen, aunque sin poder invertir su sentido de rotación en forma automática</b>. Recordemos que un transitor NPN opera mediante 3 pines: 1 "colector" en el cual se conecta el voltaje de entrada, una "base" que se liga a un pin PWM de Arduino, y un "emisor" cuya salida dependerá del valor PWM indicado en la base (un transistor PNP utiliza la misma lógica pero con polaridad invertida). De esta manera podemos aislar fácilmente el consumo del motor y controlar su abastecimiento de corriente variando el pulso enviado a la base, dentro de un rango seguro para el pin Arduino. Veamos el circuito:

<img src="https://www.mundostreaming.tv/itec/arduino/imgs/arduino_dc_pwm.png" width="800">

Atención!: la batería de 9V en la imagen, solo representa la fuente de alimentación externa, el motor incluido en el kit NO tolera este voltaje, su límite son 6V, por lo cual se podrá alimentarlo por ejemplo con una salida de 5V desde una fuente conmutada. El diodo que se observa entre el transistor y la batería, es una simple medida de protección para evitar cualquier retroalimentación de corriente desde el bobinado del motor, el agregado de un capacitor también sería útil. Un simple código bastará para ponerlo en movimiento:

````
const byte PIN_MOTOR = 9;

void setup() {
  pinMode(PIN_MOTOR, OUTPUT);
}

void loop() {
  for (byte i = 0; i <= 255; i = i + 5) {
    analogWrite(PIN_MOTOR, i);
    delay(100);
  }
  
  delay(3000);
  
  for (int i = 255; i >= 0; i = i - 5) {
    analogWrite(PIN_MOTOR, i);
    delay(100);
  }
  
  delay(3000);
}
````

Recordemos que la función <i>analogWrite</i> aplicada a un pin con soporte PWM, genera automáticamente la señal de pulso necesaria, cuyo ancho podemos variar en un rango de 0 a 255, correspondiendo lógicamente 255 al 100%, es decir, pulso alto durante la totalidad del ciclo.

En el ejemplo procedemos simplemente a acelerar de forma suave el motor hasta el regimen máximo permitido por el voltaje y el circuito utilizado, para luego desacelerar y repetir, empleando un <i>transistor BC547</i>. El tipo de transistor a usar dependerá del consumo a manejar, pudiendo optarse también por transistores Darlington o mosfets de acuerdo al caso.

Como dijimos, el circuito es muy sencillo y opera correctamente si se selecciona el tipo de transistor adecuado. Una limitación del mismo es la imposibilidad de cambiar el sentido de rotación del motor, siempre hablando de un cambio de rotación dinámica que podamos realizar mediante código en cualquier momento, no una modificación física en el circuito, ya que en ese caso solo haría falta invertir la polaridad en los cables de alimentación del motor para que éste girara en sentido contrario.

Si para nuestro proyecto es necesario contar con esta posibilidad (por ejemplo para controlar el sentido de avance de un robot u otro dispositivo), podemos utilizar un driver como el L293 o cualquier placa basada en él (como los shields para motores DC diseñados para Arduino Uno). El L293 no es más que un doble puente H que nos permitirá controlar dos motores simultáneamente. El circuito requiere algunos cables extra pero se mantiene relativamente sencillo:

<img src="https://www.mundostreaming.tv/itec/arduino/imgs/arduino_dc_pwm_l293.png" width="800">

<p>&nbsp;</p>

> <b>Recordatorio 1: al utilizar un integrado, verificar su marca semicircular y el punto, que indican orientación y pin nro 1, a efectos de no cometer errores en el orden de las conexiones</b>.

> Recordatorio 2: como siempre, estos circuitos pueden probarse de forma virtual en <a href="https://www.tinkercad.com"><b>TinkerCad</b></a> antes de testearlos físicamente.

Ya comentamos que el integrado L293 se trata de un doble puente H, cada lado del mismo nos permitirá controlar un motor. El chip requiere un extremo de alimentación para su funcionamiento (cable naranja) y otro extremo para voltaje de motores (cable rojo, una vez más recordar que en la imagen esta alimentación se representa con una batería de 9V, pero en la práctica con el motor del kit, no se deberán superar 6V), los medios de cada lado se utilizan para GND (cables negros), los siguientes externos para salida a motor (cables verdes) y los 3 pines restantes para control (cables amarillos); el de extremo (pin 5 Arduino) para habilitar (enable) y asignar regimen, los otros 2 (pines 4 y 6 Arduino) para seleccionar sentido de rotación. Así tenemos:

````
const byte ACTIVAR = 5;
const byte ENTRADA1 = 6;
const byte ENTRADA2 = 4;

void setup() {
  pinMode(ACTIVAR, INPUT);
  pinMode(ENTRADA1, OUTPUT);
  pinMode(ENTRADA2, OUTPUT);
  
  analogWrite(ACTIVAR, 128);
  digitalWrite(ENTRADA1, LOW);
  digitalWrite(ENTRADA2, HIGH);
}

void loop() {
}
````

En este ejemplo, mediante <i>analogWrite()</i> enviamos una señal PWM de aprox 50% (128, recordemos que operamos PWM de 0 a 255) al pin de activación, para indicar que el motor deberá girar a mitad de potencia. Asignando el INPUT 1 (pin 6) en bajo y el INPUT 2 (pin 4) en alto, el motor girará en sentido antihorario, invirtiéndolos lógicamente lo hará horario:

* LOW + LOW = motor detenido y libre
* LOW + HIGH = giro antihorario
* HIGH + LOW = giro horario
* HIGH + HIGH = motor detenido y energizado

<b>Ahora no solo podemos controlar inicio, parada y regimen, sino también sentido de rotación</b>, pudiendo cambiar cualquiera de estos parámetros en todo momento mediante código. Si necesitáramos otro motor, solo tendríamos que replicar las conexiones en el otro lado del integrado, y si requiriéramos más motores, sumar integrados.

<i>Por supuesto en la práctica resulta siempre más sencillo recurrir directamente a un shield o driver prearmado, que permita manejar la cantidad y potencia de motores requeridos, sea un driver basado en el L293 u otros como el chip L298 por ejemplo. Habitualmente estos drivers estarán acompañados además de alguna librería para un código más amigable.</i>.

<p>&nbsp;</p>

<b>Comparativa con servos</b>

> Tanto en robótica como en otro tipo de proyectos que requieran actuadores o motorización para movimiento, ambas opciones son aplicables. La ventaja de los servos respecto a los motores DC standard, radica en una mayor precisión de posicionamiento y el hecho de contar con un driver integrado que posibilita controlar tanto inicio, como parada, sentido de rotación y regimen, mediante un solo pin PWM, a diferencia de las soluciones para DC con L293 por ejemplo, que requieren 3 pines (1 PWM) por motor.

<p>&nbsp;</p>

<b>Otros drivers para motores DC y PAP (paso a paso)</b>

Además del característico L293 que hemos utilizado como base para los ejercicios con motores DC en el taller (sea conectándolo manualmente o aprovechándolo a través de un shiled), y la prueba directa que hemos hecho con el servo, podemos aplicar otros drivers como los siguientes:

* <b>DRV8835</b>: puede controlar 2 motores DC, hasta 12v y 1.2A por canal.

* <b>PCA9685</b>: se trata de una placa I2C que mediante los 2 pines de control, permite manejar hasta 16 salidas PWM con resolución de 12 bit. Muy útil cuando queremos organizar la conexión de varios servos en un proyecto.

* <b>A397 (EasyDriver)</b>: otro driver muy conocido para motores PAP de 7 a 30V y unos 750 mA por fase.

* <b>A4988</b>: driver muy popular para impresoras 3D, que obviamente se puede aplicar a otros proyectos. Permite controlar un motor PAP bipolar de 8 a 35V y hasta 2A por fase.

* <b>L9110S</b>: un doble puente H para controlar 2 motores DC de 2.5 a 12V y hasta 800 mA por fase.

* <b>HG7881</b>: driver basado en el integrado L9110, que permite manejar 4 motores DC, una alternativa compacta para pequeños robots.

* <b>L298N</b>: otro módulo doble puente H, muy popular, que permite manejar 2 motores DC o un motor PAP bipolar de 5 a 35V y hasta 2A por salida.