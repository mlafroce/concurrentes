#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include "../../common-util/signals/Process.h"
#include "../../common-util/MessageQueue.h"
#include "../../common-util/message/MessageSender.h"

class Client : public Process {
public:
    Client();
    void query(const std::string& query);
    void start();

private:
    MessageSender sender;
    const int id;
    void connect();
    void displayResult(const std::string& result);
};

#endif // CLIENT_H
