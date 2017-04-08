#include "DaringGame.h"

#include "Card.h"
#include "Player.h"

DaringGame::DaringGame(int numPlayers) :
	numPlayers(numPlayers) {
	playerList.reserve(numPlayers);
	for (char i = 0; i < this->numPlayers; ++i) {
		playerList.emplace_back(Player{i});
	}
}

DaringGame::~DaringGame() {
	stop();
}

void DaringGame::start() {
	for (int i = 0; i < this->numPlayers; ++i) {
		playerList[i].start();
	}
	// No se que ponerle para que no haga busy-waiting
	for (int i = 0; i < this->numPlayers; ++i) {
		playerList[i].join();
	}
}

void DaringGame::stop() {
	for (int i = 0; i < this->numPlayers; ++i) {
		playerList[i].stop();
	}
}