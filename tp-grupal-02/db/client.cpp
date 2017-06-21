#include "../common-util/Log.h"
#include "../common-util/signals/SignalHandler.h"
#include "../common-util/signals/SIGINT_Handler.h"

#include "../db/core/Client.h"

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
    Log* log = Log::getInstance();
    log->setFile("client.log");
    log->info("Iniciando cliente");
    
    Client client;
    SIGINT_Handler sigIntHandler(client);
    SignalHandler::getInstance()->registerHandler(SIGINT, &sigIntHandler);
    
//     try {
//         while (client.isRunning()) {
//             client.query();
//         }
//     } catch (const std::string& e) {
//         log->error(e.c_str());
//     } catch (const IpcException& e) {
//         log->error(e.what());
//     }
    
    client.test();
    
    SignalHandler::deleteInstance();
    Log::deleteInstance();
}
