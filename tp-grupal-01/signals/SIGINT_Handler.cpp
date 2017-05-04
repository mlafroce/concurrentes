#include "SIGINT_Handler.h"
#include "../game/DaringGame.h"

SIGINT_Handler::SIGINT_Handler(DaringGame& game)
	: game(game) {}

SIGINT_Handler::~SIGINT_Handler() {}

int SIGINT_Handler::handleSignal(int signum) {
	game.stop();
	return 0;
}
