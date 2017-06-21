#include "Server.h"
#include "../../common-util/Log.h"
#include "../../common-util/signals/SignalHandler.h"
#include "../../common-util/signals/SIGINT_Handler.h"
#include "../../common-util/IpcException.h"

Server::Server() :
    sender(0),
    ipcDestroy(true){}

Server::~Server() {
    if (ipcDestroy) {
        sender.destroy();
    }
}

int Server::listenClients() {
    LOG_INFO("Escuchando nuevos clientes");
    int clientPid = sender.takeClient();
    LOG_INFO("El proceso " + std::to_string(clientPid) + " intenta comunicarse");
    return clientPid;
}

int Server::attend(int clientId) {
    sender.setId(clientId);
    bool exit = false;
    while (!exit) {
        std::string clientCmd = sender.receive();
        
        exit = clientCmd.compare("exit") == 0;

        sender.send(execute(clientCmd));
    }
    return 0;
}

void Server::preventIpcDestroy() {
    ipcDestroy = false;
}


std::string Server::execute(const std::string& clientCmd) {
    LOG_DEBUG("El cliente intenta ejecutar \"" + clientCmd + "\"");
    return std::string("Se ejecuta ") + clientCmd;
}

void Server::run() {
    SIGINT_Handler sigIntHandler(*this);
    SignalHandler::getInstance()->registerHandler(SIGINT, &sigIntHandler);
    try {
        while (this->isRunning()) {
            int pidCliente = this->listenClients();
            pid_t pid = fork();
            if (pid == 0) {
                this->preventIpcDestroy();
                LOG_INFO("Aceptando mensajes del cliente " + std::to_string(pidCliente));
                this->attend(pidCliente);
                exit(0);
            }
        }
    } catch (const std::string& e) {
        LOG_ERROR(e.c_str());
    } catch (const IpcException& e) {
        LOG_ERROR(e.what());
    }

    // TODO Agregar un signal handler para sigcld que haga waitpid(-1, 0, 0);

    SignalHandler::deleteInstance();
}
