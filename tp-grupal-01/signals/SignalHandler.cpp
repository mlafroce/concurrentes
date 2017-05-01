#include <memory.h>
#include "SignalHandler.h"

SignalHandler* SignalHandler::instance = NULL;
EventHandler* SignalHandler::signal_handlers [NSIG];

SignalHandler::SignalHandler () {
}

SignalHandler* SignalHandler::getInstance () {

	if (instance == NULL)
		instance = new SignalHandler ();

	return instance;
}

void SignalHandler::deleteInstance () {
	if (instance != NULL) {
		delete instance;
		instance = NULL;
	}
}

EventHandler* SignalHandler::registerHandler(int signum, EventHandler* eh) {

	EventHandler* old_eh = SignalHandler::signal_handlers[signum];
	SignalHandler::signal_handlers [signum] = eh;

	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SignalHandler::dispatcher;
	// inicializa la mascara de seniales a bloquear durante la ejecucion del
	// handler como vacio
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask,signum);
	sigaction(signum,&sa,0);	// cambiar accion de la senial

	return old_eh;
}

void SignalHandler::dispatcher(int signum) {
	if(SignalHandler::signal_handlers[signum] != 0 )
		SignalHandler::signal_handlers[signum]->handleSignal(signum);
}

int SignalHandler::removeHandler(int signum) {
	SignalHandler::signal_handlers[signum] = NULL;
	return 0;
}
