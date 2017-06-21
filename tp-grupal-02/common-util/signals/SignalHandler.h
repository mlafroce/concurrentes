#ifndef SIGNALHANDLER_H_
#define SIGNALHANDLER_H_

#include <signal.h>

#include "EventHandler.h"

class SignalHandler {

	private:
		static SignalHandler* instance;
		static EventHandler* signal_handlers [NSIG];

		SignalHandler (void);
		static void dispatcher(int signum);

	public:
		static SignalHandler* getInstance();
		static void deleteInstance();
		EventHandler* registerHandler (int signum,EventHandler* eh);
		int removeHandler (int signum);

};

#endif /* SIGNALHANDLER_H_ */
