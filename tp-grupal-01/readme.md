<img src="https://drive.google.com/uc?id=0B0t-E7izp738eWZWQjJtU09TSVY4am9jNE5Fb2twb0pxWHZB" width="300">

### 75.59 - Tecnicas de programacion concurrente I - FIUBA

## 1er Proyecto | DaringGame

* [Bert, Tomás Augusto (95606)](https://github.com/tbert12)

* [Etchanchú, Facundo Matías (95604)](https://github.com/FacuEt)

* [Lafroce, Matías Ezequiel (91378)](https://github.com/mlafroce)



# Supuestos

Al momento de implementar la aplicación, se tomaron en cuenta las siguientes precondiciones:

* Para que se produzca la victoria, además de quedarse sin cartas, el jugador debe impedir levantar la pila de descarte. Es decir, jugar la "mano" sin cartas.

* La cantidad de jugadores es menor a la mitad de cartas del mazo, de forma que haya al menos una ronda completa antes de una victoria.

* El proceso se ejecuta en un entorno en el cual se puede crear un directorio con los archivos que serán utilizados como claves en la generación de mecanismos de IPC

# Diseño

## Clases principales

### Main

En el hilo de ejecución main ocurren los siguientes hechos:

* Se instancia la lógica del juego, se cargan las configuraciones y se inicializan los mecanismos de IPC

* Se agrega un handler de señales (SIGINT)

* Se instancian los procesos por cada jugador

* Se instancia un proceso para el árbitro.

Una vez realizados estos pasos, el hilo se queda esperando a que sus hijos terminen para liberar sus recurso.

### Jugador 

La clase jugador es la que contiene el loop principal de juego por cada jugador. El mismo reside dentro de **DaringGame**, siendo este último el que le provee las cartas iniciales al jugador.

Cada jugador posee una pila de cartas propias, y una referencia a *TurnManager*, clase que le ayudará en la comunicación interprocesos.

### Turn Manager

Posee referencias a mecanismos de comunicación y sincronización para los jugadores. Estos mecanismos son:

* Contador de turno en memoria compartida: se utiliza para que cada proceso pueda saber el turno de quién es.

* Barrera de inicio de turno, de procesamiento: Se utilizan dos "barreras" para sincronizar dos etapas importantes del turno del jugador: jugar una carta en la mesa, y procesar la carta jugada.

Esta clase además posee funciones para que el jugador sepa si es su turno y para que pueda pasar el turno a otro jugador una vez terminado el suyo.

### Mesa

  Administra toda la información que es pública para todos los jugadores. Lo que en la vida real vemos sobre la mesa de juego (cartas jugadas, cantidad de cartas de cada jugador, ganador, manos sobre el pilón, etc).

  Estas variables son almacenadas en memoria compartida, de esta manera los jugadores podrán saber en cualquier momento el estado de la mesa de juego.

### Acciones

  Acciones engloba todas las "jugadas" que se realizan cada vez que se muestra una carta que requiere una. En esta clase se registran qué jugador realiza la acción guardando el orden temporal que se realiza la misma, es de suma importancia tener registrados de dicha forma los datos ya que los jugadores por medio de la **Acción** requiere saber si los demás jugadores la hicieron y también si fue el último en realizarla dado que en algunos casos (número de carta repetida o carta con valor 7) debe llevarse la pila de cartas descartadas.

  La forma en que esta entidad guarda los datos y sincroniza todos los procesos es a través de un contador en memoria compartida que registra la cantidad de jugadores que realizaron la acción. Y para guardar de forma ordenada quien va realizando las acciones se utiliza un archivo bloqueante en donde se va escribiendo de una forma serializada un vector de los jugadores que hicieron la acción.

  A su vez hay 2 tipos de Acciones Acción Simple y Acción de Mano. Acción Simple permite realizar las acciones tales como "venia", “Buenos días Señorita”, “Buenas noches caballero” o gritar “Atrevido”. Acción de Mano (HandAction) simula cuando los jugadores ponen la mano sobre la pila de descarte.

### Log

  Se utiliza un log (en un patrón singleton) protegido por un lockfile. El log posee un formato con el cual se imprime la hora, severidad del mensaje, y proceso que lo lanzó. Este se inicializa en el proceso inicial y es liberado (eliminada instancia) cuando el procesos principal finaliza.

### Árbitro

  El fin de esta clase es mostrar información de la partida como la cantidad de cartas que le queda a cada jugador, cuál fue la última carta apilada y mostrar un ganador (si lo hay). Esto lo hace por medio de una instancia de la mesa ya que, como se menciona anteriormente,  contiene toda la información que es pública para todos los jugadores.

## Soluciones a eventos específicos

### Repartir Cartas

  Las cartas se reparten desde el proceso padre al proceso hijo por medio de un pipe previo a arrancar el juego. De esta manera, las cartas se "barajan" una única vez en el proceso padre, y los hijos (que destruyen la copia propia de las cartas barajadas) toman el subset de cartas enviados por el padre.

### Turnos

  Los turnos están divididos en 2 etapas: procesar (es decir, ver y actuar de acuerdo a) la carta que está sobre la mesa, y jugar una carta nueva. Estas dos etapas están separadas por mecanismos de barrera que se encargan de que todos los procesos lleguen hasta la barrera antes de seguir procesando.

Se utilizó un contador de turnos para saber de quién es el turno a jugar.

### Cartas jugadas

Las cartas jugadas se almacenan en memoria dinámica, por medio de una clase llamada *Table*, que representa la mesa en donde se desarrolla el juego. Esta clase almacena las cartas arrojadas a la mesa en un PIPE, es decir se emula el pilón físico de cartas. 

Cuando un jugador tiene que tomar todas las cartas del pilón (por las circunstancias del juego) se las pide a *Table* y esta las toma del PIPE, que por su definición cuando extrae del mismo se borran quedando vacío.

Además del PIPE la clase también almacena las dos últimas cartas jugadas en memoria compartida. De esta manera se evita tener que extraer del PIPE las dos últimas cartas y volver a agregarlas (ya que se borran) cada vez que un proceso las solicite.

### Última jugador en poner su mano sobre el pilón 

Al igual que las cartas jugadas, se utiliza la clase *Table* para tomar registro, en memoria compartida, de quien fue el último jugador en poner su mano sobre el pilón cuando ocurre el evento "Atrevido" o “número repetido”.

Hay dos variables en memoria compartida: una que determina la cantidad de jugadores que pusieron su mano sobre el pilón, y la otra que almacena el identificador del último jugador en apoyar la mano. De esta manera cuando el contador iguala la cantidad de jugadores sabemos que ese jugador fue el último, por ende el que debe tomar las cartas de la mesa.

### Todos los jugadores se debe escuchar y ver

Es una sub-etapa de procesar la carta y surge cuando una carta jugada/descartada requiere que los jugador realicen una acción. Cada jugador (*proceso*) crea un instancia de la acción (mencionada en las clases) qué va a realizar, luego la realizan dicha acción y por medio de una barrera se bloquea y espera que los demás jugadores hagan lo mismo. Justo en ese momento que se "levanta" la barrera cada jugador está asegurado que todos los otros jugadores realizaron la acción, de esta forma simulamos que todos los jugadores se “escucharon” y se “vieron”.

### Ganador

El jugador que se queda sin cartas en la mano envía una señal al padre para avisar que él fue el proceso ganador, y luego se encarga de liberar recursos.

El ciclo de cada jugador (proceso) lo primero que hace (después de esperar la barrera de turno) es verificar que haya un ganador en la mesa. Si lo hay, inmediatamente sale del loop. Para ello, en la mesa hay una memoria compartida que contiene el id del ganador. Inicialmente es un valor inválido (-1), por lo tanto para que haya un ganador el valor tiene que ser mayor o igual a 0 (referenciando al id del jugador que ganó).

El momento que el jugador le avisa a la mesa que hay un ganador es posteriormente al evento de procesar la carta (*ver primer supuesto*). Luego de procesar la carta verifica cuantas cartas tiene en su pila y si no tiene ninguna procede a avisarle a la mesa.

### Árbitro puede ver la cantidad de cartas que le quedan a cada jugador

En paralelo a los jugadores, desde el procesos principal, se lanza un proceso que será el "árbitro", el procesos solo creara una instancia a la clase arbitro (la configurar, si se desea cambiar algun parametro), se pasa la misma instancia de Mesa que fue utilizada para crear a los jugadores y lo corre. Al correrlo el árbitro entra en un ciclo que se repite cada un cierto intervalo parametrizable. Cada vez que realiza el loop escribe en el log, de una forma amigable, la información de la mesa. El ciclo finaliza (e inmediatamente el proceso también) cuando el árbitro se entera que la partida terminó ya que detecta que hay un ganador.

Es importante mencionar que se discutieron varias formas de cómo implementar el árbitro. Las alternativas eran, además de la que se implementó, permitirle al usuario que ejecuta el juego escribir comandos por *STDIN* para pedir información de la mesa o permitir correr el ejecutable con un parámetro para mostrar la información de la mesa. Dado que la simulación de la partida no supera el segundo de ejecución y no se simula "tiempo real", se hace prácticamente imposible la interacción con el usuario. De esta forma se optó por la alternativa de un proceso en paralelo a la partida con un ciclo que se repite en un intervalo muy pequeño de tiempo (actualmente 1 milisegundo).

## Diagramas

### Clases

![image alt text](https://drive.google.com/uc?id=0B0t-E7izp738NmZNVEd5eC1pZ2c)

### Interacción entre clases principales

![image alt text](https://drive.google.com/uc?id=0B__btMWqGOUeQ0V5VWFydTl5UW8)

### Ciclo principal del proceso jugador

![image alt text](https://drive.google.com/uc?id=0B__btMWqGOUeMVhYeW1EV2J1QXM)

### Diagrama de estados del jugador

![image alt text](https://drive.google.com/uc?id=0B__btMWqGOUebkc0SW14MnRwTHM)



