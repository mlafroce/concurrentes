#include "Client.h"
#include "../../common-util/Log.h"
#include "../../../tp-grupal-01/util/SharedMemory.h"
#include <iostream>
#include <signal.h>

#define CLIENT_TIMEOUT 5
#define CLIENT_CONNECTED 1
#define CLIENT_NOT_CONNECTED 0

Client::Client() :
    id(getpid()),
    sender(getpid(),false){}


void Client::query(const std::string& query) {
    sender.send(query);
    LOG_DEBUG("Query enviado. Esperando respuesta del server");
    displayResult(sender.receive());
}

void Client::connect() {
    SharedMemory<int> connected("client." + std::to_string(this->id) + ".ipc",'t');
    connected.write(CLIENT_NOT_CONNECTED);
    if (fork() == 0) {
        sleep(CLIENT_TIMEOUT);
        if (connected.read() == CLIENT_NOT_CONNECTED) {
            std::cout << "ERROR: No se puede conectar con el servidor [TIMEOUT]" << std::endl;
            LOG_ERROR("No se puede conectar al servidor TIMEOUT");
            kill(getppid(),SIGINT);
            sender.destroy();
        }
        exit(0);
    }
    sender.connect();
    LOG_INFO("El cliente " + std::to_string(this->id) + " intenta conectarse");
    if ( sender.isConnected() ) {
        connected.write(CLIENT_CONNECTED);
        LOG_INFO("Cliente " + std::to_string(this->id) + " conectado");
    } else {
        LOG_WARNING("Error en la conexion con el servidor")
    }
}

void Client::displayResult(const std::string& result) {
    LOG_DEBUG("Servidor responde");
    std::cout << result << std::endl;
    LOG_DEBUG(result);
}

void Client::work() {
    this->connect();

    while (this->isRunning()) {
        std::string query;
        std::cout << "> ";
        std::getline(std::cin, query);
        LOG_INFO("Leido query, preparado para enviar: \"" + query + "\"");
        this->query(query);
        if (query.compare("exit") == 0) {
            this->stop();
        }
    }
    LOG_DEBUG("Finalizado trabjo de Cliente " + std::to_string(this->id));
}

