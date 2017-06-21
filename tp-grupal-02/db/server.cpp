#include "../common-util/Log.h"
#include "../common-util/IpcException.h"
#include "../common-util/signals/SignalHandler.h"
#include "../common-util/signals/SIGINT_Handler.h"

#include "core/Server.h"

void initLog() {
    Log* log = Log::getInstance();
    log->setFile("server.log");
    log->showTimePrecision(true);
    log->showInSTDOUT(true);
    log->setLevel(DEBUG);
    LOG_INFO("Iniciando servidor");
}

void freeMemory() {
    Log::deleteInstance();
}

int main() {
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
    initLog();

    Server server;
    server.start();

    freeMemory();
}


