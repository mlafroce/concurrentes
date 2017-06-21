#include "core/Client.h"

#include "../common-util/Log.h"

void initLog() {
    Log* log = Log::getInstance();
    log->setFile("client.log");
    log->setLevel(DEBUG);
    log->showTimePrecision(true);
    log->showInSTDOUT(false);
    LOG_INFO("Iniciando cliente");
}

void freeMemory() {
    Log::deleteInstance();
}

int main () {
    /*
     * TODO:
     *      - Ciclo que hace stdin (input humano)
     *      - Cada vez que presiona enter:
     *          > Genera message poniendo su id como emisor y lo que se lee del stdin en el body
     *              Message(getpid(),0,stdin)
     *          > Pone el mensaje SERIALIZDO en la cola de entrada
     *          > ESPERA (sleep? bloqueo?) a leer un mensaje que tenga su id en la cola de salida.
     */

    initLog();

    Client client;
    client.start();
    
    freeMemory();
}

