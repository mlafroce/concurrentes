#ifndef CLIENT_H
#define CLIENT_H
#include "../../common-util/signals/Process.h"
#include "../../common-util/MessageQueue.h"

class Client : public Process {
public:
    Client();
    void query();
    void test();
private:
    MessageQueueBase mq;
};

#endif // CLIENT_H
