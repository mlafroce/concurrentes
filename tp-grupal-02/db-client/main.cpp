#include <iostream>
#include <zconf.h>

int main () {
    std::cout << "DB Client [id=" <<  getpid() << "]" << std::endl;
    /*
     * TODO:
     *      - Ciclo que hace stdin (input humano)
     *      - Cada vez que presiona enter:
     *          > Genera message poniendo su id como emisor y lo que se lee del stdin en el body
     *              Message(getpid(),0,stdin)
     *          > Pone el mensaje SERIALIZDO en la cola de entrada
     *          > ESPERA (sleep? bloqueo?) a leer un mensaje que tenga su id en la cola de salida.
     */
}

