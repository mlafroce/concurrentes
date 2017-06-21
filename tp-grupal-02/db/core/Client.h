#ifndef CLIENT_H
#define CLIENT_H
#include <string>
#include "../../common-util/signals/Process.h"
#include "../../common-util/MessageQueue.h"
#include "../../common-util/message/MessageSender.h"

class Client : public Process {
public:
    Client();

private:
    MessageSender sender;
    const int id;
    void connect();
    void query(const std::string& query);
    void displayResult(const std::string& result);
    void work();

};

#endif // CLIENT_H
