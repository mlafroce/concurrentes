#include <vector>
#include "MessageSender.h"
#include "../Log.h"

#define CONNECT_TYPE 1
#define CONNECTION_ESTABLISHED 34265

MessageSender::MessageSender(int aId, bool isServer_) :
    mqQuery("db-messages", 'q'),
    id(aId),
    isServer(isServer_),
    mqResult("db-messages",'r') {}

void MessageSender::send(const std::string &message) {
    Message msg(message);
    MessageQueueBase medium = this->isServer ? mqResult : mqQuery;

    int size = msg.size() + 1;
    medium.sendMessage(&size, sizeof(int), this->id);
    const char* msgBuf = msg.serialize();
    medium.sendMessage(msgBuf, size, this->id);
    std::string medium_name = this->isServer ? "mqResult" : "mqQuery";
    LOG_DEBUG("Enviado mensaje a " +
                      medium_name + " (id: " + std::to_string(id) + ") " +
                      "\"" + std::string(msgBuf) + "\" " +
                      "(" + std::to_string(size) + ")"
    );
}

std::string MessageSender::receive() {
    MessageQueueBase medium = this->isServer ? mqQuery : mqResult;

    int msgLen;
    medium.recvMessage(&msgLen, sizeof(int), id);

    std::vector<char>msgBuf((unsigned long)msgLen);
    medium.recvMessage(msgBuf.data(), msgLen, id);
    std::string medium_name = this->isServer ? "mqQuery" : "mqResult";
    LOG_DEBUG("Leido mensaje de " + medium_name + " (id: " + std::to_string(id) + ") \"" + std::string(msgBuf.data()) + "\" (" + std::to_string(msgLen) + ")" )

    Message msg(msgBuf.data());
    return msg.getMessage();
}

void MessageSender::destroy() {
    mqQuery.destroyMessageQueue();
    mqResult.destroyMessageQueue();
}

void MessageSender::connect() {
    LOG_DEBUG("Envio: " + std::to_string(this->id));
    mqQuery.sendMessage(&this->id, sizeof(int), CONNECT_TYPE);
}

int MessageSender::takeClient() {
    int clienId;
    mqQuery.recvMessage(&clienId, sizeof(int), CONNECT_TYPE);
    int code = CONNECTION_ESTABLISHED;
    mqResult.sendMessage(&code, sizeof(int), clienId);
    return clienId;
}

bool MessageSender::isConnected() {
    int result;
    mqResult.recvMessage(&result, sizeof(int), this->id);
    return result == CONNECTION_ESTABLISHED;
}
