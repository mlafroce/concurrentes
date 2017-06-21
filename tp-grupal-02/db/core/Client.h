#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include "../../common-util/signals/Process.h"
#include "../../common-util/MessageQueue.h"

class Client : public Process {
public:
    Client();
    void query(const std::string& query);
    void connect();
private:
    MessageQueueBase mqQuery;
    MessageQueueBase mqResult;
    const int id;
    void displayResult(const std::string& result);
};

#endif // CLIENT_H
