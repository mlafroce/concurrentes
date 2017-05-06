#include "TurnManager.h"
#include "Player.h"
#include "../log/Log.h"

const std::string TurnManager::barrierFilename("turn_manager_barrier.ipc");
const std::string TurnManager::sharedMemoryFilename("turn_manager_sharedmemory.ipc");

TurnManager::TurnManager(int numPlayers) 
	: numPlayers(numPlayers),
	turnCounter(sharedMemoryFilename, 't'),
	barTurnBegin(barrierFilename, 'b', numPlayers),
	barProcessCard(barrierFilename, 'p', numPlayers),
	barAction(barrierFilename,'a',numPlayers) {
		int firstTurn = Utils::randomInt(0,numPlayers-1);
		LOG_INFO("Iniciado TurnManager, primer turno para el Jugador " + std::to_string(firstTurn));
		turnCounter.write( firstTurn );
	}

void TurnManager::waitToTurnBegin() {
	this->barTurnBegin.wait();
}

void TurnManager::waitToProcessCard() {
	this->barProcessCard.wait();
}

void TurnManager::waitToDoAction() {
	this->barAction.wait();
}

bool TurnManager::isMyTurn(const Player& player) {
	return player.getId() == this->turnCounter.read();
}

void TurnManager::passTurn() {
	int curTurn = this->turnCounter.read() + 1;
	curTurn %= numPlayers;
	LOG_INFO("Asignando turno a " + std::to_string(curTurn));
	this->turnCounter.write(curTurn);
}

void TurnManager::freeBarriers() {
	this->barTurnBegin.free();
	this->barProcessCard.free();
	this->barAction.free();
}

int TurnManager::getNumberPlayers() {
    return numPlayers;
}
