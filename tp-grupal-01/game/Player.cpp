#include "Player.h"
#include <cstdio>
#include <vector>
#include <unistd.h>

#include "TurnManager.h"

Player::Player(char playerId, TurnManager& turnManager) : 
	Thread(), turnManager(turnManager), id(playerId), running(false){}

void Player::run() {
	this->running = true;
	printf("Arrancando el jugador %d\n", this->id);
	while (this->running) {
		turnManager.waitToTurnBegin();
		if (this->turnManager.isMyTurn(*this)) {
			playCard();
			turnManager.waitToProcessCard();
			this->turnManager.passTurn();
		} else {
			turnManager.waitToProcessCard();
		}
		processCard();
	}
	// Destrabo barreras 
	turnManager.freeBarriers();
	printf("Listo para join%d\n", this->id);
}

void Player::stop() {
	printf("Jugador[%d]->stop()\n", this->id);
	this->running = false;
}

void Player::playCard() {
	printf("El jugador %d juega una carta\n", this->getId());
}

void Player::processCard() {
	printf("El jugador %d procesa una carta\n", this->getId());
}

char Player::getId() const {
	return this->id;
}
