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
		turnManager.wait(*this);
		printf("Jugando %d\n", this->id);
		turnManager.signalNext(*this);
	}
	printf("Listo para join%d\n", this->id);
}

void Player::stop() {
	printf("Jugador[%d]->stop()\n", this->id);
	this->running = false;
}

void Player::take(const Card& card) {
	this->cards.push_back(card);
}

char Player::getId() const {
	return this->id;
}
