#include "SIGINT_Handler.h"
#include "Process.h"

SIGINT_Handler::SIGINT_Handler(Process& process)
	: process(process) {}

SIGINT_Handler::~SIGINT_Handler() {}

int SIGINT_Handler::handleSignal(int signum) {
	process.stop();
	return 0;
}
