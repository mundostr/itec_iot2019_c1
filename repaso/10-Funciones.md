<h1><b>FUNDACION INSTITUTO TECNOLOGICO RAFAELA</b></h1>
<h2><b>Taller Arduino Adultos 2019</b></h2>

<h3>10- Funciones</h3>

En los códigos que hemos escrito hasta el momento, hemos tenido oportunidad de utilizar funciones predefinidas del entorno Arduino, las propias <i>setup()</i> y <i>loop()</i> por ejemplo, pero no hemos hablado sobre los detalles de uso de este tipo de estructuras.

<b>Sintéticamente, una función es un bloque de código identificado bajo un nombe arbitrario, que no se ejecuta de forma directa sino al ser invocado a través de una llamada a la función</b>. Supongamos el siguiente ejemplo básico:

```
float valor = 22.38;
float resultado;

void setup() {
  Serial.begin(38400);
  resultado = PI * valor;
  Serial.print("Resultado: ");
  Serial.println(resultado); 
}

void loop() {
}
```

Tomamos un valor decimal <i>valor</i> y calculamos un resultado multiplicándolo por 3.14 (aprovechamos para ello la constante <i>PI</i> predefinida de Arduino). Podríamos reescribir el código para realizar el cálculo dentro de una función, declarándola e invocándola de esta manera:

```
float valor = 22.38;
float resultado;

void setup() {
  Serial.begin(38400);
  operacion();
  Serial.print("Resultado: ");
  Serial.println(resultado); 
}

void loop() {
}

void operacion() {
  resultado = PI * valor;
}
```

Cuando la ejecución del flujo principal de código alcance la llamada a <i>operacion()</i>, se redirigirá al bloque contenido dentro de la definición de la función (en este caso solo la línea resultado = PI * valor;), ejecutará este código y retornará a la secuencia inicial, siguiendo desde alli (con Serial.print("Resultado: "); y los demás comandos).

La palabra reservada <i>void</i> en la definición de operacion(), al igual que en <i>setup()</i> y <i>loop()</i>, se utiliza para indicar que la función no retorna ningún valor, solo ejecuta su contenido y vuelve al flujo principal. Veremos luego cómo se modifica esta definición cuando necesitamos retornar valores.

Si bien el ejemplo es válido, en primera instancia no parece muy atractivo, hemos escrito varias líneas más de código solo para lograr lo mismo. <b>La ventaja real de las funciones radica en una mejor organización del código, fundamentalmente cuando debemos reutilizar varias veces los mismos fragmentos, como veremos a continuación</b>.

<p>&nbsp;</p>

<b>Funciones y argumentos</b>

No estamos limitados solo a encapsular código en funciones, podemos también pasar <i>argumentos</i> a las mismas para que utilicen en el código que contienen, y devolver valores si es necesario. Supongamos que necesitamos imprimir por consola una línea de trazos, pero de longitud variable:

```
void setup() {
  Serial.begin(38400);
  Serial.println("Todo OK");
  lineaTrazos(20);
}

void loop() {
  /* Otras líneas de código que necesitamos ejecutar */
  lineaTrazos(20);
  /* Más líneas de código */
  lineaTrazos(8);
}

void lineaTrazos(byte longitud) {
  for (byte x = 1; x <= longitud; x++) {
    Serial.print("-");
  }
  Serial.println();
}
```

Empleando una función y pasándole un argumento (byte longitud), podemos encapsular y organizar el código, dejando una llamada limpia en los lugares donde necesitamos la línea. Obviamente en cada uno de esos lugares, en vez de repetir el ciclo for, simplemente invocamos a la función y le pasamos el argumento para indicarle de qué longitud queremos la línea.

> Por supuesto no estamos limitados a un solo argumento, podemos indicar la cantidad que necesitemos separados por comas, cada uno de ellos con su tipo de dato correspondiente. Ejemplo: void lineaTrazos(byte longitud, boolean retornoCarro).

<p>&nbsp;</p>

<b>Retorno de valores</b>

Si no indicamos nada, la función ejecutará por defecto su código interno, y el control retornará a la línea de código inmediatamente posterior a la que realizó la llamada, para seguir secuencialmente con lo demás.

Si en cambio deseamos por ejemplo asignar un resultado generado por la función a una variable, podemos hacerlo de manera directa:

```
void setup() {
  Serial.begin(38400);
  int lectura = analogRead(A3);

  Serial.println("Lectura previa: ");
  Serial.println(calculo(lectura, 3));

  /* Acá ejecutamos más código, inicializamos un sensor por ej. */

  Serial.println("Lectura posterior: ");
  Serial.println(calculo(lectura, 2));
}

void loop() {
}

float calculo(float indice, int coeficiente) {
  return (PI * indice) / coeficiente;
}
```

> Nuevamente, mientras mayor cantidad de veces necesitemos reutilizar los mismos comandos -sea con iguales o distintos argumentos- más útil resultará encapsularlos en una función para limpiar el código principal.

<p>&nbsp;</p>

<b>Alcance (scope) de variables</b>

Al escribir código Arduino sencillo, declaramos las variables a utilizar al comienzo del programa (fuera de <i>setup()</i> y <i>loop()</i>), con lo cual estas variables son de tipo <i>global</i>, es decir, pueden ser empleadas en cualquier parte del código.

Si bien esta práctica es válida, a medida que el volumen y la complejidad de código crecen, administrar todas las variables globalmente se vuelve un problema, sea de rendimiento en casos puntuales, o lo más habitual, de lectura y depuración de código, ya que todas pueden ser modificadas libremente desde cualquier fracción del programa, lo cual es mucho más propenso a errores y dificulta el rastreo de los mismos.

<b>Al utilizar funciones, podemos declarar variables internamente, y éstas se mantendrán válidas solo dentro del ámbito de la función, es decir, su alcance o scope será el de la propia función en la que fueron declaradas, no existiendo fuera de ellas. Serán por ende variables <i>locales</i></b>. En el caso anterior:

```
float calculo(float indice, int coeficiente) {
  float operacion = PI * indice;
  float final;

  switch(coeficiente) {
    case 2:
      final = operacion;
      break;
    case 3:
      final = operacion / coeficiente
   }

   return final;
}
```

Tanto <i>operación</i> como <i>final</i> serán variables locales, si intentamos utilizar o modificar su valor fuera de la función calculo(), se generará un error.

> Atención!: return final, solo retorna el valor de la variable como resultado de la función, para ser asignado a donde corresponda, NO devuelve la variable en sí. En el ejemplo es utilizado directamente en el Serial.println (Serial.println(calculo(lectura, 3));).

Nuevamente, el alcance de las variables permite una mejor organización y depuración de código a medida que éste crece, no solo en funciones sino también en <i>objetos</i>, como veremos más adelante. En el caso de los <i>objetos</i>, tanto las variables como los propios <i>métodos</i> definidos en sus <i>clases</i> también utilizarán el scope, permitiendo ajustarlos como <i>públicos</i> o <i>privados</i> según se requiera.