#include <iostream>
#include "core/Client.h"

#include "../common-util/Log.h"

void initLog() {
    Log* log = Log::getInstance();
    log->setFile("client.log");
    log->setLevel(DEBUG);
    log->showTimePrecision(true);
    log->showInSTDOUT(false);
    LOG_INFO("Iniciando cliente");
}

void freeMemory() {
    Log::deleteInstance();
}

int main () {
    initLog();

    Client client;
    client.start();
    freeMemory();
}

