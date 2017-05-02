#include "Player.h"
#include <cstdio>
#include <vector>
#include <unistd.h>

#include "TurnManager.h"
#include "../Log/Log.h"

Player::Player(TurnManager& turnManager) : 
	turnManager(turnManager), running(false){}

void Player::start(int id) {
	this->id = id;
	
	this->running = true;
	LOG_INFO("Arrancando el jugador " + std::string(1, 48 + this->id));
	play();
}

void Player::stop() {
	this->running = false;
}

void Player::play() {
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
}


void Player::playCard() {
	Card card = this->cards.back();
	this->cards.pop_back();
	LOG_INFO("El jugador " + std::string(1, 48 + this->id)
	+ " jugó " + card.toString());
}

void Player::processCard() {
	sleep(1);
}

void Player::addCards(const std::vector<Card>& cards) {
	this->cards.insert(this->cards.end(), cards.begin(), cards.end());
}


char Player::getId() const {
	return this->id;
}
