#ifndef SERVER_H
#define SERVER_H
#include <string>
#include "../../common-util/signals/Process.h"
#include "../../common-util/MessageQueue.h"
#include "../../common-util/LockFile.h"
#include "../../common-util/message/MessageSender.h"


class Server : public Process {
public:
    Server();
    ~Server();
    /**
     * Devuelve pid del cliente entrante
     */
    int listenClients();
    int attend(int clientId);
    void run();
    void preventIpcDestroy();
private:
    std::string execute(const std::string& clientCmd);
    MessageSender sender;
    bool ipcDestroy;
};

#endif // SERVER_H
