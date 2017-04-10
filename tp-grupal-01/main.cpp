#include "signals/SignalHandler.h"
#include "signals/SIGINT_Handler.h"
#include <cstdio>
#include <cstdlib>

#include "game/DaringGame.h"

int getOptions(int argc, char** argv);

int main(int argc, char** argv) {
	int numPlayers = getOptions(argc, argv);

    DaringGame game(numPlayers);
	SIGINT_Handler sigIntHandler(game);
	SignalHandler::getInstance()->registerHandler(SIGINT, &sigIntHandler);

    game.start();

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
