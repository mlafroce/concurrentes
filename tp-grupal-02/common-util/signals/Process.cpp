#include "Process.h"

Process::Process() : running(true) {}

bool Process::isRunning() {
    return running;
}

void Process::stop() {
    running = false;
}
