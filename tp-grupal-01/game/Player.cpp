#include "Player.h"
#include <cstdio>
#include <vector>
#include <unistd.h>

#include "TurnManager.h"
#include "../Log/Log.h"


Player::Player(TurnManager& turnManager) :
	turnManager(turnManager), running(false),table(Table()){}

void Player::start(int id) {
	this->id = id;
    this->running = true;
    table.setNumberOfCards(this->getId(), (int) cards.size());
	LOG_INFO("Arrancando el jugador " + std::string(1, 48 + this->id));
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

void Player::stop() {
	this->running = false;
}

void Player::playCard() {
	LOG_INFO("El jugador " + std::to_string(this->getId()) +"juega una carta\n");
    //Card card = cards.pop_back();
    //table.pushCard(card,this->getId());
}

void Player::processCard() {
	printf("El jugador %d procesa una carta\n", this->getId());
}

char Player::getId() const {
	return this->id;
}
