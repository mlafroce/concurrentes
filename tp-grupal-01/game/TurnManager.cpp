#include "TurnManager.h"
#include "Player.h"

#include <cstdio>

TurnManager::TurnManager (const std::vector<Player>& players) {
	this->semaphores.reserve(players.size());
	for (int i = 0; i < players.size(); ++i) {
		this->semaphores.emplace_back(Semaphore{0});
	}
}

void TurnManager::signalAll() {
	for (int i = 0; i < semaphores.size(); ++i) {
		this->semaphores[i].signal();
	}
}

void TurnManager::signalNext(const Player& player) {
	char nextPlayer = player.getId();
	nextPlayer = ++nextPlayer % semaphores.size();
	semaphores.at(nextPlayer).signal();
}

void TurnManager::wait(const Player& player) {
	semaphores.at(player.getId()).wait();
}
