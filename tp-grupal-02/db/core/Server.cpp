#include "Server.h"
#include "../../common-util/Log.h"
#include "../../common-util/Utils.h"
#include <cstdio>
#include <string>

Server::Server() :
    mqQuery(Utils::generateKey("db-messages", 'q')),
    mqResult(Utils::generateKey("db-messages", 'r')),
    ipcDestroy(true){}

Server::~Server() {
    if (ipcDestroy) {
        mqQuery.destroyMessageQueue();
        mqResult.destroyMessageQueue();
    }
}

int Server::listenClients() {
    int clientPid;
    Log* log = Log::getInstance();
    log->info("Escuchando nuevos clientes");
    this->mqQuery.recvMessage(&clientPid, sizeof(int), 1);
    char buf[80];
    snprintf(buf, 80, "El proceso %d intenta comunicarse", clientPid);
    log->info(buf);
    return clientPid;
}

int Server::attend(int clientId) {
    bool exit;
    Log* log = Log::getInstance();
    while (!exit) {
        int msgLen;
        this->mqQuery.recvMessage(&msgLen, sizeof(int), clientId);
        std::vector<char>msgBuf(msgLen);
        this->mqQuery.recvMessage(msgBuf.data(), msgLen, clientId);
        std::string clientCmd(msgBuf.data());
        
        exit = clientCmd.compare("exit") == 0;

        std::string response = execute(clientCmd);
        msgLen = response.size() + 1;
        this->mqResult.sendMessage(&msgLen, sizeof(int), clientId);
        this->mqResult.sendMessage(response.c_str(), msgLen, clientId);
    }
    return 0;
}

void Server::preventIpcDestroy() {
    ipcDestroy = false;
}


std::string Server::execute(const std::string& clientCmd) {
    Log* log = Log::getInstance();
    std::string logMsg("El cliente intenta ejecutar ");
    logMsg.append(clientCmd);
    log->debug(logMsg);
    return std::string("Se ejecuta ") + clientCmd;
}
