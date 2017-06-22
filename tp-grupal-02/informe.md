# 75.59 - Tecnicas de programacion concurrente I - FIUBA

## 2do Proyecto | Base de datos

* [Bert, Tomás Augusto (95606)](https://github.com/tbert12)

* [Etchanchú, Facundo Matías (95604)](https://github.com/FacuEt)

* [Lafroce, Matías Ezequiel (91378)](https://github.com/mlafroce)

# Supuestos

Al momento de implementar la aplicación, se tomaron en cuenta las siguientes precondiciones:

* Sólo se implementan altas y lecturas.

* La consulta ingresada por el cliente mapea a una sola tabla igual a la del enunciado.

## Diseño

### Clases principales

#### server.cpp

Es el hilo principal que levanta el servidor.

#### Server 

La clase **Servidor** contiene la lógica para recibir los mensajes de los clientes, procesarlos y responder correspondientemente. 

Mantiene un ciclo hasta que se reciba una señal SIGINT para detener el proceso. Para funcionar interactúa con dos clases principales:

* **Table**, se encarga de gestionar la base de datos física.

* **MessageSender**, se encarga de gestionar la comunicación entre los clientes y el servidor.

#### Table

Es la clase encargada de manipular los datos en la DB. Para esto utiliza un archivo en donde se guardan todas las entradas de la tabla en formato csv.

Para proteger y sincronizar el acceso al archivo (tabla) se utiliza la clase **LockFile**, que se encarga de lockear el archivo de la manera correcta para realizar la acción correspondiente sin inconvenientes.

**Table** tiene un sólo método público llamado ***execute*** que recibe un query (string) y realiza la operación correspondiente, retornando las entradas o el mensaje adecuado.

#### MessageSender

Administra el dialogo entre los clientes y el servidor. Utiliza dos colas de mensajes:

* **mqQuery** Cola de mensajes por la que el cliente envía mensajes (querys) al servidor.

* **mqResponse** Cola de mensajes por la que el servidor le responde las consultas al cliente.

Posee un método **connect()** con el que inicia una "conexión" con el cliente.

También posee un método **takeClient()** con el que se queda bloqueado hasta que un cliente se conecta, y devuelve el id del cliente conectado. 

#### client.cpp

Archivo donde se encuentra la función **main()** del cliente

#### Client

La clase **Cliente** posee un MessageSender al igual que el servidor, que utiliza para comunicarse con él.

## Diagramas

### Clases

### Interacción entre clases principales

### Diagrama de estados de la base de datos

