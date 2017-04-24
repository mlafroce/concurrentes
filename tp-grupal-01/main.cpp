#include "signals/SignalHandler.h"
#include "signals/SIGINT_Handler.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sys/wait.h>


#include "game/DaringGame.h"
#include "Log/Log.h"

int getOptions(int argc, char** argv);

int main(int argc, char** argv) {
	int numPlayers = getOptions(argc, argv);

    Log::getInstance()->setLevel(DEBUG);
    Log::getInstance()->setFile("DaringGame.log");
    Log::getInstance()->showInSTDOUT(true);

    DaringGame game(numPlayers);
    LOG_INFO("Juego inicializado con " + std::to_string(numPlayers) + " jugadores.");

    SIGINT_Handler sigIntHandler(game);
	SignalHandler::getInstance()->registerHandler(SIGINT, &sigIntHandler);

	bool imParent = false;
	for (int i = 0; i < numPlayers; i++) {
		pid_t pid = fork();
		if (pid == 0) {
			game.start(i);
		} 
	}
	for (int i = 0; i < numPlayers; i++) {
		waitpid(-1, 0, 0);
	}

    SignalHandler::destruir();
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
