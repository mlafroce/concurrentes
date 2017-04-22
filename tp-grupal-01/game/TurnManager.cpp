#include "TurnManager.h"
#include "Player.h"

#include <cstdio>

TurnManager::TurnManager(const std::vector<Player>& players) 
	: numPlayers(players.size()), turnCounter(0),
	barTurnBegin("",numPlayers), barProcessCard("",numPlayers) {}

void TurnManager::waitToTurnBegin() {
	this->barTurnBegin.wait();
}

void TurnManager::waitToProcessCard() {
	this->barProcessCard.wait();
}

bool TurnManager::isMyTurn(const Player& player) {
	return player.getId() == this->turnCounter;
}

void TurnManager::passTurn() {
	this->turnCounter = ++this->turnCounter % this->numPlayers;
}

void TurnManager::freeBarriers() {
	this->barTurnBegin.free();
	this->barProcessCard.free();
}
