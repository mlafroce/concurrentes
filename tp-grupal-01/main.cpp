#include "signals/SignalHandler.h"
#include "signals/SIGINT_Handler.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <sys/wait.h>

#include "game/DaringGame.h"
#include "log/Log.h"
#include "game/Referee.h"

int getOptions(int argc, char** argv);
void freeMemory();
void initLog();
bool wakeReferee(DaringGame game);

int main(int argc, char** argv) {
	int numPlayers = getOptions(argc, argv);

	initLog();

    DaringGame game(numPlayers);

    SIGINT_Handler sigIntHandler(game);
	SignalHandler::getInstance()->registerHandler(SIGINT, &sigIntHandler);

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

	if (wakeReferee(game)) {
        return 0;
    }

	for (int i = 0; i < numPlayers + 1; i++) {
		waitpid(-1, 0, 0);
	}

    freeMemory();
    return 0;
}

bool wakeReferee(DaringGame game) {
	pid_t pid = fork();
	if (pid == 0) {
		Table tableGame = game.getTable();
		Referee ref(tableGame);
		LOG_DEBUG("Arbitro creado");
		ref.setInterval(1);
        ref.start();
        LOG_DEBUG("Arbitro finalizó");
		return true;
	} else {
        LOG_INFO("Se creó proceso arbitro con pid = " + std::to_string(pid));
    }
    return false;
}

void initLog() {
	Log* log = Log::getInstance();
	log->setLevel(INFO);
	log->setFile("DaringGame.log");
	log->showInSTDOUT(true);
    log->showTimePrecision(true);
	log->info("===== Nueva ejecucion de DaringGame =====");
}

void freeMemory() {
	LOG_INFO("Limpio memoria y salgo");
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
