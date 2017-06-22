#include "Process.h"
#include "SIGINT_Handler.h"
#include "SIGCHLD_Handler.h"
#include "SignalHandler.h"
#include "../Log.h"
#include "../IpcException.h"

Process::Process() : running(true) {}

bool Process::isRunning() {
    return running;
}

void Process::stop() {
    running = false;
}

void Process::start() {
    SIGINT_Handler sigIntHandler(*this);
	SIGCHLD_Handler sigChldHandler(*this);
    SignalHandler::getInstance()->registerHandler(SIGINT, &sigIntHandler);
    SignalHandler::getInstance()->registerHandler(SIGCHLD, &sigChldHandler);
    try {
        this->work();
    } catch (const std::string& e) {
        LOG_ERROR(e.c_str());
    } catch (const IpcException& e) {
        LOG_ERROR(e.what());
    }

    // TODO Agregar un signal handler para sigcld que haga waitpid(-1, 0, 0);

    SignalHandler::deleteInstance();
}
