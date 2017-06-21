#include "Client.h"
#include "../../common-util/Log.h"
#include "../../common-util/Utils.h"
#include <cstdio>

Client::Client() :
    mq(Utils::generateKey("db-messages", 'a')) {}


void Client::query() {

}

void Client::test() {
    int pid = getpid();
    Log* log = Log::getInstance();
    mq.sendMessage(&pid, sizeof(int), 1);
    char buf[80];
    snprintf(buf, 80, "El cliente %d intenta comunicarse", pid);
    log->info(buf);
}
