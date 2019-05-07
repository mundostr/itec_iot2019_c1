<h1><b>FUNDACION INSTITUTO TECNOLOGICO RAFAELA</b></h1>
<h2><b>Taller IOT 2019 C1</b></h2>

<h3>05- Consola y plotter serial en Arduino IDE</h3>

<p>&nbsp;</p>

<b>Consola</b>

<img src="http://mundostreaming.tv/itec/arduino/imgs/arduino_consola_serie.png" width="800">

Utilizando el menu <i>Herramientas -> Monitor Serie</i> del Arduino IDE, accedemos a la consola serial incorporada en el programa. Para poder abrir esta consola, necesitaremos que nuestro Arduino se encuentre conectado vía USB, y por supuesto, elegido el puerto correspondiente. Para manejarnos dentro del código, utilizaremos el objeto <i>Serial</i>, ya definido en las librerías incorporadas de Arduino.

<b>Inicialización de consola</b>

```
void setup() {
  Serial.begin(38400);
}
```

El argumento <b>38400 indica la velocidad del puerto en baudios</b> (otros valores habituales son por ej 9600, 19200, 57600, 115200). Para utilizar el puerto podemos elegir diferentes valores, aunque uno alto como 115200 puede generarlos problemas, dependiendo de la placa específica que estemos utilizando. 38400 es un rango razonable, con buen equilibrio entre velocidad y compatibilidad.

Una vez activado el <i>Serial</i>, podremos "imprimir" cualquier valor que necesitemos chequear, por ej el de la variable frecParpadeo que hemos venido empleando en los ejemplos, mediante:

```
Serial.print(frecParpadeo);
Serial.println(frecParpadeo);
```

Ambas instrucciones envían el valor de frecParpadeo a la consola serial, la segunda agrega un salto de línea luego de imprimir.

Con estas simples líneas, podremos sacar en cualquier momento el valor de cualquier variable a consola, para monitorear su estado, por supuesto también podremos revisar el valor de entrada recibido en diferentes pines (como el de un botón por ejemplo), o cualquier indicador que necesitemos chequear.

> Si se observan caracteres ascii en la consola, en lugar de una impresión legible, verificar en la zona inferior derecha de la ventana de consola, que el valor de baudios elegido sea el mismo configurado en Serial.begin() dentro del código.

Como alternativa gráfica al monitor, disponemos del plotter serial (<i>Herramientas -> Serial Plotter</i>), que en lugar de imprimirnos los valores numéricos o de texto recibidos, nos dará una representación gráfica de éstos en función del tiempo, muy cómodo para revisar el estado de señales de entrada como pulsadores o sensores.

<img src="http://mundostreaming.tv/itec/arduino/imgs/arduino_plotter_serie.png" width="800">

La consola serial también puede emplearse como <b>entrada</b> para la carga de configuraciones u opciones, algo que veremos más adelante en el taller. No obstante <b>debemos tener siempre presente que la activación de consola supone una pequeña ralentización en la ejecución del código</b>, razón por la cual debemos aprovecharla mayormente para depuración del funcionamiento de nuestro programa -y solo en casos justificados- como entrada o habilitada continuamente en un código de producción.

<p>&nbsp;</p>

Otros detalles de interés sobre puerto serie:

<b><a href="https://www.luisllamas.es/arduino-puerto-serie/">www.luisllamas.es/arduino-puerto-serie</a></b>