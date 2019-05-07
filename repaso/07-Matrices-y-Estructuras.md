<h1><b>FUNDACION INSTITUTO TECNOLOGICO RAFAELA</b></h1>
<h2><b>Taller IOT 2019 C1</b></h2>

<h3>07- Matrices y Estructuras</h3>

<p>&nbsp;</p>

<b>Matrices</b>

En muchas oportunidades, vamos a tener necesidad de almacenar datos en bloques para poder manejarlos con mayor comodidad. <b>Una matriz no es más que una colección de variables que comparten el mismo nombre, y se diferencian entre sí por un índice que indica su ubicación dentro de la colección</b>. Esto nos permite ganar claridad y organizar de manera más conveniente nuestro código, facilitando el pasaje de valores a funciones y demás elementos.

La asignación se realiza identificando también el tipo de dato con el que se va a trabajar, pero agregando corchetes ([ y ]) al nombre, y encerrando los items que componen la matriz entre llaves, separados por comas. De esta forma, si queremos declarar una matriz llamada mtrNumeros, que almacene 4 números enteros, escribimos:

```
int mtrNumeros[] = {2, 6, 3, 2};
```

o bien, si conocemos de antemano la cantidad de items que contendrá, reservamos solo la cantidad específica de espacios necesarios:

```
int mtrNumeros[4] = {2, 6, 3, 2};
```

> Recordar que en los tipos de datos capaces de manejar tanto valores positivos como negativos, podemos ahorrar recursos utilizando el modificador "unsigned" por delante, si sabemos que dichos valores no serán nunca negativos. Para esta declaración sería:

```
unsigned int mtrNumeros[4] = {2, 6, 3, 2};
```

mtrNumeros se declara entonces como una matriz (array) de 4 elementos, que serán números enteros positivos. Lógicamente, si cambiamos cualquiera de los items a un número negativo, al momento de compilar obtendremos un error.

La lectura o asignación de valores se realiza utilizando el índice de ubicación del item en la matriz, <b>pero cuidado!, recordando siempre que dicho índice comienza en 0, no en 1</b>. Si escribimos por ejemplo:

```
int var01 = mtrNumeros[1];
```

la variable var01 asumirá el valor 6

si queremos actualizar ese 6 a por ejemplo un 11, colocamos:

```
mtrNumeros[1] = 11;
```

Ejemplo. :

```
unsigned int mtrNumeros[] = {2, 6, 3, 2};
unsigned int sumatoria = 0;

void setup() {
  Serial.begin(38400);
  
  for (byte i = 0; i < 4; i++) {
    sumatoria = sumatoria + mtrNumeros[i];
    Serial.println(mtrNumeros[i]);
  }

  Serial.println();
  Serial.println(sumatoria);
}

void loop() {
}
```

<p>&nbsp;</p>

<b>Recorrer una matriz con límites fijos o sizeof()</b>

Si conocemos de antemano la cantidad de items de la matriz, podemos fácilmente recorrerla colocando valores fijos en nuestro ciclo <i>for</i>, como lo hemos hecho en el ejemplo anterior (<i>for (byte i = 0; i < 4; i++) {</i>).

Si en cambio deseamos automatizarlo, o si tenemos necesidad de trabajar con matrices de tamaño variable (resultados de logueo de sensores por ejemplo), en las cuales no sabemos la cantidad exacta de items contenidos, podemos calcular el límite de ciclo de esta forma:

````
const float MATRIZ[] = { 6.5, 3.1, 5.5 };

for (byte x = 0; x < sizeof(MATRIZ) / sizeof(float); x++) {
  // Ejecutamos el código necesario para cada item de la matriz
}
````

<i>sizeof(MATRIZ)</i> nos retorna el tamaño total en <b>bytes</b> de la matriz, mientras que <i>sizeof(float)</i> nos devuelve el tamaño en <b>bytes</b> de un float (es decir, 4), que es el tipo de dato con el cual hemos declarado la matriz. Dividiendo los bytes totales sobre los bytes de cada dato, obtendremos la cantidad de items. En el ejemplo sería 12 / 4 = 3.