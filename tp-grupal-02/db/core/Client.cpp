#include "Client.h"
#include "../../common-util/Log.h"
#include "../../common-util/IpcException.h"
#include "../../common-util/signals/SignalHandler.h"
#include "../../common-util/signals/SIGINT_Handler.h"
#include <iostream>

Client::Client() :
    id(getpid()),
    sender(id){}


void Client::query(const std::string& query) {
    /*
    int msgLen;
    msgLen = (int)query.size() + 1;
    mqQuery.sendMessage(&msgLen, sizeof(int), this->id);
    mqQuery.sendMessage(query.c_str(), msgLen, this->id);
    
    mqResult.recvMessage(&msgLen, sizeof(int), this->id);
    std::vector<char>msgBuf((unsigned long)msgLen);
    mqResult.recvMessage(msgBuf.data(), msgLen, this->id);
    std::string result(msgBuf.data());
    */
    sender.send(query);
    LOG_DEBUG("Query enviado \"" + query + "\"");
    displayResult(sender.receive());
}

void Client::connect() {
    sender.connect();
    LOG_INFO("El cliente " + std::to_string(this->id) + " intenta comunicarse");
}

void Client::displayResult(const std::string& result) {
    std::cout << result << std::endl;
    LOG_DEBUG(result);
}

void Client::work() {
    this->connect();

    while (this->isRunning()) {
        std::string query;
        std::cout << "> ";
        std::getline(std::cin, query);
        LOG_INFO("Enviando: " + query);
        this->query(query);
    }
}

