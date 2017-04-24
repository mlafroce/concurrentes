#include "DaringGame.h"

#include <algorithm>
#include "Card.h"
#include "Player.h"

DaringGame::DaringGame(int numPlayers) :
	turnManager(numPlayers), player(turnManager), numPlayers(numPlayers) {
	dealCards();
}

DaringGame::~DaringGame() {
	stop();
}

void DaringGame::start(int id) {
	player.start(id);
}

void DaringGame::stop() {
	player.stop();
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
