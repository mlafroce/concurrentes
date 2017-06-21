#include "Client.h"
#include "../../common-util/Log.h"
#include "../../common-util/Utils.h"
#include <cstdio>

Client::Client() :
    mqQuery(Utils::generateKey("db-messages", 'q')),
    mqResult(Utils::generateKey("db-messages", 'r')),
    id(getpid()){}


void Client::query(const std::string& query) {
    int msgLen;
    msgLen = query.size() + 1;
    mqQuery.sendMessage(&msgLen, sizeof(int), this->id);
    mqQuery.sendMessage(query.c_str(), msgLen, this->id);
    
    mqResult.recvMessage(&msgLen, sizeof(int), this->id);
    std::vector<char>msgBuf(msgLen);
    mqResult.recvMessage(msgBuf.data(), msgLen, this->id);
    std::string result(msgBuf.data());
    displayResult(result);
}

void Client::connect() {
    Log* log = Log::getInstance();
    mqQuery.sendMessage(&this->id, sizeof(int), 1);
    char buf[80];
    snprintf(buf, 80, "El cliente %d intenta comunicarse", 1);
    log->info(buf);
}

void Client::displayResult(const std::string& result) {
    Log* log = Log::getInstance();
    log->debug(result);
}

