#ifndef SERVER_H
#define SERVER_H
#include "../../common-util/signals/Process.h"
#include "../../common-util/MessageQueue.h"

class Server : public Process {
public:
    Server();
    ~Server();
    /**
     * Devuelve pid del cliente entrante
     */
    int listenClients();
    void attend(int clientId);
private:
    MessageQueueBase mq;
};

#endif // SERVER_H
