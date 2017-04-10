#include "DaringGame.h"

#include <algorithm>
#include "Card.h"
#include "Player.h"

DaringGame::DaringGame(int numPlayers) :
	turnManager(playerList), numPlayers(numPlayers) {
	playerList.reserve(numPlayers);
	for (char i = 0; i < this->numPlayers; ++i) {
		playerList.emplace_back(Player{i, this->turnManager});
	}
	turnManager = TurnManager(playerList);
	dealCards();
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

void DaringGame::dealCards() {
	std::vector<Card> cards;
	for (char i = 0; i < Card::MaxCardRank; ++i) {
		cards.push_back(Card{CardSuit::A, i});
		cards.push_back(Card{CardSuit::B, i});
		cards.push_back(Card{CardSuit::C, i});
		cards.push_back(Card{CardSuit::D, i});
	}
	std::random_shuffle(cards.begin(), cards.end());
	for (int i = 0; i < cards.size(); i++) {
		//playerList[i % this->numPlayers].take(cards[i]);
	}
}
