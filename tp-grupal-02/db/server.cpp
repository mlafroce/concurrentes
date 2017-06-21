#include "../common-util/Log.h"
#include "../common-util/IpcException.h"
#include "../common-util/signals/SignalHandler.h"
#include "../common-util/signals/SIGINT_Handler.h"

#include "core/Server.h"

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
    Log* log = Log::getInstance();
    log->setFile("server.log");
    log->info("Iniciando servidor");
    Server server;
    SIGINT_Handler sigIntHandler(server);
    SignalHandler::getInstance()->registerHandler(SIGINT, &sigIntHandler);
    try {
        while (server.isRunning()) {
            int pidCliente = server.listenClients();
            pid_t pid = fork();
            if (pid == 0) {
                log->info(std::string("Aceptando mensajes del cliente ")
                + std::to_string(pidCliente));
                server.attend(pidCliente);
                return;
            } 
        }
    } catch (const std::string& e) {
        log->error(e.c_str());
    } catch (const IpcException& e) {
        log->error(e.what());
    }
    
    SignalHandler::deleteInstance();
    Log::deleteInstance();
}


