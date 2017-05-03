#include "signals/SignalHandler.h"
#include "signals/SIGINT_Handler.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sys/wait.h>

#include "game/DaringGame.h"
#include "log/Log.h"
#include "util/Pipe.h"

int getOptions(int argc, char** argv);
void freeMemory();
void initLog();

int main(int argc, char** argv) {
	int numPlayers = getOptions(argc, argv);

    initLog();

    DaringGame game(numPlayers);
    LOG_INFO("Juego inicializado con " + std::to_string(numPlayers) + " jugadores.");

    SIGINT_Handler sigIntHandler(game);
	SignalHandler::getInstance()->registerHandler(SIGINT, &sigIntHandler);

	bool imParent = false;
	for (int i = 0; i < numPlayers; i++) {
		Pipe cardPipe;
		pid_t pid = fork();
		if (pid == 0) {
			int result = game.start(i, cardPipe);
			return result;
		} else {
			game.sendCards(i, cardPipe);
		}
	}
	for (int i = 0; i < numPlayers; i++) {
		waitpid(-1, 0, 0);
	}

}

void initLog() {
	Log* log = Log::getInstance();
	log->setLevel(DEBUG);
	log->setFile("DaringGame.log");
	log->showInSTDOUT(true);
}

void freeMemory() {
	LOG_INFO("Free memory and exit");
	Log::deleteInstance();
	SignalHandler::deleteInstance();
}

int getOptions(int argc, char** argv) {
	if(argc < 2) {
		printf("Para iniciar el juego, debe indicar la cantidad de jugadores por parámetro\n");
		exit(-1);
	}
	int numPlayers = atoi(argv[1]);
	if (numPlayers < 4 || numPlayers % 2){
		printf("El número de jugadores debe ser par y mayor o igual a 4\n");
		exit(-1);
	}
	return numPlayers;
}
