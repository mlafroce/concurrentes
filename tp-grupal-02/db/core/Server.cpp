#include "Server.h"
#include "../../common-util/Log.h"
#include "../../common-util/Utils.h"
#include <cstdio>

Server::Server() :
    mq(Utils::generateKey("db-messages", 'a')) {}

Server::~Server() {
    mq.destroyMessageQueue();
}

int Server::listenClients() {
    int clientPid;
    Log* log = Log::getInstance();
    log->info("Escuchando nuevos clientes");
    mq.recvMessage(&clientPid, sizeof(int), 1);
    char buf[80];
    snprintf(buf, 80, "El proceso %d intenta comunicarse", clientPid);
    log->info(buf);
    return clientPid;
}

void Server::attend(int clientId) {

}


