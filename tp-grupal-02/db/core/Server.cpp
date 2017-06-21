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
        LOG_DEBUG("LLega mensaje de " + std::to_string(clientId) + "\n\t\"" + clientCmd + "\"");
        sender.send(execute(clientCmd));
        exit = clientCmd.compare("exit") == 0;
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

void Server::work() {
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
}

