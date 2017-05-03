#include "DaringGame.h"

#include <algorithm>
#include "Card.h"
#include "Player.h"
#include "../log/Log.h"
#include "../util/Pipe.h"

DaringGame::DaringGame(int numPlayers) :
	turnManager(numPlayers), player(turnManager), numPlayers(numPlayers) {
	shuffleCards();
    LOG_INFO("Juego inicializado con " + std::to_string(numPlayers) + " jugadores.");
}

DaringGame::~DaringGame() {}

int DaringGame::start(int id, Pipe& cardStream) {
	this->initialCards.clear();
	receiveCards(cardStream);
	player.start(id);
	return 0;
}

void DaringGame::stop() {
	player.stop();
}

void DaringGame::receiveCards(Pipe& cardStream) {
	int numCards = 0;
	Card defaultCard(A, 0);
	cardStream.read(&numCards, sizeof(int));
	std::vector<Card> newCards(numCards, defaultCard);
	cardStream.read(newCards.data(), sizeof(defaultCard) * numCards);
	LOG_INFO("Player id: " + std::to_string(player.getId()) + std::string(" recibió ") + std::to_string(numCards) + " cartas");
    std::string cards;
    for (Card &card : newCards) {
        cards += "\n\t " + card.toString();
    }
    LOG_DEBUG("Player id: " + std::to_string(player.getId()) + "\n\tCartas recibidas:" + cards);
	player.addCards(newCards);
}

void DaringGame::sendCards(int id, Pipe& cardStream) {
	int cardsToSend = this->initialCards.size() / this->numPlayers;
	if (id == (this->numPlayers - 1)) {
		cardsToSend += this->initialCards.size() % this->numPlayers;
	}
	int firstCard = this->initialCards.size() / this->numPlayers;
	firstCard *= id;
	Card* cardBuff = &this->initialCards[firstCard];
	cardStream.write(&cardsToSend, sizeof(cardsToSend));
	cardStream.write(cardBuff, sizeof(*cardBuff) * cardsToSend);
}


void DaringGame::shuffleCards() {
	for (char i = 1; i <= Card::MaxCardRank; ++i) {
		this->initialCards.push_back(Card{CardSuit::A, i});
		this->initialCards.push_back(Card{CardSuit::B, i});
		this->initialCards.push_back(Card{CardSuit::C, i});
		this->initialCards.push_back(Card{CardSuit::D, i});
	}
	std::random_shuffle(this->initialCards.begin(), this->initialCards.end());
}

Table DaringGame::getTable() const {
    return player.getTable();
}
