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
    log->showInSTDOUT(false);
    log->setLevel(DEBUG);
    LOG_INFO("Iniciando servidor");
}

void freeMemory() {
    Log::deleteInstance();
}

int main() {
    initLog();

    Server server;
    std::cout << ">>>> TPC I - Server iniciado <<<<" << std::endl << std::endl;
    server.start();

    freeMemory();
    std::cout << ">>>> TPC I - Adiosss <<<<" << std::endl << std::endl;
}


