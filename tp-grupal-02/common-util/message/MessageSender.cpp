#include <vector>
#include "MessageSender.h"

#define CONNECT_TYPE 1

MessageSender::MessageSender(int aId) :
    mqQuery("db-messages", 'q'),
    id(aId),
    mqResult("db-messages",'r') {}

void MessageSender::send(const std::string &message) {
    Message msg(id,message);
    int size = msg.size();
    mqQuery.sendMessage(&size, sizeof(int), msg.getId());
    mqQuery.sendMessage(msg.serialize(), size, msg.getId());
}

std::string MessageSender::receive() {
    int msgLen;
    mqResult.recvMessage(&msgLen, sizeof(int), id);
    std::vector<char>msgBuf((unsigned long)msgLen);
    mqResult.recvMessage(msgBuf.data(), msgLen, id);
    Message msg(msgBuf.data());
    return msg.getMessage();

}

void MessageSender::destroy() {
    mqQuery.destroyMessageQueue();
    mqResult.destroyMessageQueue();
}

void MessageSender::connect() {
    mqQuery.sendMessage(&this->id, sizeof(int), CONNECT_TYPE);
}

int MessageSender::takeClient() {
    int clienId;
    mqQuery.recvMessage(&clienId, sizeof(int), CONNECT_TYPE);
    return clienId;
}
