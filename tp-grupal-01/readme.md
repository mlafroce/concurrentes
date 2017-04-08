# TP Grupal N° 1

## Diseño

### Paso 1: Turnos

El primer problema que se decidió atacar fue el traspaso de turnos.
Para esto se utilizó un semáforo por jugador, de manera que el turno del jugador quede bloqueado hasta que reciba una señal.

Cada jugador tiene un semáforo asociado que lo detiene antes de comenzar su turno. Al iniciar el juego, uno de estos semáforos es levantado, ejecuta sus acciones y finaliza su turno enviandole una señal al semáforo del jugador siguiente. Automáticamente se queda esperando.

### Paso 2: Interaccion con la carta descartada

El siguiente paso fue crear un mecanismo con el que todos los hilos despierten cuando el jugador tira una carta.
Para esto se agregó una función "Procesar carta" directamente después del semáforo de inicio de turno.
Luego de procesar la carta, sólo el jugador con turno accede a una porción de código especial donde tira una carta, envía una señal al semáforo de todos los jugadores para que "procesen" la carta que se tiró, proceso la carta que acabo de tirar, y le habilito el turno al siguiente jugador.
Como habilitar el turno puede generar una condition race donde quierajugar una carta sin que se haya terminado de jugar el turno anterior, al finalizar el turno de los jugadores pongo una barrera de forma que estén todos sincronizados.
