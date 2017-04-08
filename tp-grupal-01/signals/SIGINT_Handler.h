#ifndef SIGINT_HANDLER_H_
#define SIGINT_HANDLER_H_

#include "EventHandler.h"

class DaringGame;

class SIGINT_Handler : public EventHandler {
private:
	DaringGame& game;

public:
	explicit SIGINT_Handler(DaringGame& game);
	~SIGINT_Handler ();

	virtual int handleSignal(int signum);
};

#endif /* SIGINT_HANDLER_H_ */
