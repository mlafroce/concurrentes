#ifndef CONCURRENTES_MESSAGESENDER_H
#define CONCURRENTES_MESSAGESENDER_H


#include "Message.h"
#include "../MessageQueue.h"

class MessageSender {
private:
    MessageQueueBase mqQuery;
    MessageQueueBase mqResult;
    int id;
    bool isServer;
public:
    MessageSender(int id,bool isServer = false);
    ~MessageSender(){};

    void setId(int nId){id = nId;};

    void connect();
    int takeClient();
    void send(const std::string &message);
    std::string receive();

    bool isConnected();

    void destroy();
};


#endif //CONCURRENTES_MESSAGESENDER_H
