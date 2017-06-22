#ifndef SIGCHLD_HANDLER_H_
#define SIGCHLD_HANDLER_H_

#include "EventHandler.h"

class Process;

class SIGCHLD_Handler : public EventHandler {
private:
	Process& process;

public:
	explicit SIGCHLD_Handler(Process& process);
	~SIGCHLD_Handler ();

	virtual int handleSignal(int signum);
};

#endif /* SIGCHLD_HANDLER_H_ */
