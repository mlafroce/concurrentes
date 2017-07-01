#include <iostream>
#include "../common-util/Log.h"
#include "../common-util/IpcException.h"
#include "../common-util/signals/SignalHandler.h"
#include "../common-util/signals/SIGINT_Handler.h"

#include "core/Server.h"

void initLog() {
    Log* log = Log::getInstance();
    log->setFile("server.log");
    log->showTimePrecision(true);
    log->showInSTDOUT(true);
    log->setLevel(DEBUG);
    LOG_INFO("Iniciando servidor");
}

void freeMemory() {
    Log::deleteInstance();
}

int main() {
    initLog();

    Server server;
    server.start();

    freeMemory();
}


