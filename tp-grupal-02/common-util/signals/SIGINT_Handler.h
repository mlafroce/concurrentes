#ifndef SIGINT_HANDLER_H_
#define SIGINT_HANDLER_H_

#include "EventHandler.h"

class Process;

class SIGINT_Handler : public EventHandler {
private:
	Process& process;

public:
	explicit SIGINT_Handler(Process& process);
	~SIGINT_Handler ();

	virtual int handleSignal(int signum);
};

#endif /* SIGINT_HANDLER_H_ */
