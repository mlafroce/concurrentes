#include <iostream>
#include "core/Table.h"

int main() {
    std::cout << "DB Server" << std::endl;

    /*
     * TODO:
     *      - Ciclo que espera mensajes de una "cola de entrada" (Message).
     *      - Cada vez que lee uno:
     *          > Hace fork
     *          > Deserializa el Message
     *          > Guarda de quien es el mensaje (<<from_id>>: Message.getTransmitter)
     *          > Atiende la consulta (Message.getMessage)
     *          > Genera un nuevo mensaje con resultado:
     *              Message(getpid() | 0,<<from_id>>, table.execute(msg_entrante))
     *                      ^^^^^^^
     *                 Al cliente no le importa, solo hay 1 server
     *          > Lo serializa y lo pone en la "cola de salida"
     */
}


