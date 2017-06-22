#include "SIGCHLD_Handler.h"
#include "Process.h"
#include <sys/types.h>
#include <sys/wait.h>

#include "../Log.h"

SIGCHLD_Handler::SIGCHLD_Handler(Process& process)
	: process(process) {}

SIGCHLD_Handler::~SIGCHLD_Handler() {}

int SIGCHLD_Handler::handleSignal(int signum) {
	pid_t pid;
	while (pid = waitpid(-1, 0, WNOHANG) > 1) {
		LOG_INFO("Escuchador " + std::to_string(pid) + " destruido");
	}
	return 0;
}
