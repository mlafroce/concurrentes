#include "Player.h"
#include <cstdio>
#include <vector>
#include <unistd.h>

#include "TurnManager.h"
#include "../Log/Log.h"


Player::Player(TurnManager& turnManager) :
	turnManager(turnManager), running(false),table(Table(turnManager.getNumberPlayers())){}

void Player::start(int id) {
	this->id = id;
	this->running = true;
	LOG_INFO("Iniciando la mesa del jugador " + std::string(1, 48 + this->id));
    table.setNumberOfCards(this->getId(), (int) cards.size());
	play();
}

void Player::stop() {
	this->running = false;
}

void Player::play() {
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


void Player::playCard() {
	Card card = this->cards.back();
	this->cards.pop_back();
	LOG_INFO("El jugador " + std::string(1, 48 + this->id)
	+ " jugó " + card.toString() );
    table.pushCard(card,this->getId());
}

void Player::processCard() {
	sleep(1);
    Card lastCard = table.getLastCard();
    if (false){
        std::vector<Card> cards = table.takeAllCards(this->getId());
        this->addCards(cards);
    }

}

void Player::addCards(const std::vector<Card>& cards) {
	this->cards.insert(this->cards.end(), cards.begin(), cards.end());
}


int Player::getId() const {
	return this->id;
}
