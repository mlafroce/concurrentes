#include "Server.h"
#include "../../common-util/Log.h"

Server::Server() :
    sender(0, true),
    ipcDestroy(true){}

Server::~Server() {
    if (ipcDestroy) {
        sender.destroy();
    }
}

int Server::listenClients() {
    LOG_INFO("Escuchando nuevos clientes");
    int clientPid = sender.takeClient();
    LOG_INFO("El proceso " + std::to_string(clientPid) + " solicita conexión");
    return clientPid;
}

int Server::attend(int clientId) {
    sender.setId(clientId);
    bool exit = false;
    while (!exit) {
        LOG_DEBUG("Esperando mensaje de cliente " + std::to_string(clientId));
        std::string clientCmd = sender.receive();
        LOG_DEBUG("LLega mensaje de " + std::to_string(clientId) + ". Genero y envio respuesta\n\t\"" + clientCmd + "\"");
        sender.send(execute(clientCmd));
        LOG_DEBUG("Respuesta enviada");
        exit = clientCmd.compare("exit") == 0;
    }
    return 0;
}

void Server::preventIpcDestroy() {
    ipcDestroy = false;
}


std::string Server::execute(const std::string& clientCmd) {
    LOG_DEBUG("El cliente intenta ejecutar \"" + clientCmd + "\"");
    return table.execute(clientCmd);
}

void Server::work() {
    while (this->isRunning()) {
        int pidCliente = this->listenClients();
        pid_t pid = fork();
        if (pid == 0) {
            this->preventIpcDestroy();
            LOG_INFO("Conectado con cliente " + std::to_string(pidCliente));
            this->attend(pidCliente);
            LOG_INFO("Finalizada conexión con cliente " + std::to_string(pidCliente));
            exit(0);
        }
    }
}

