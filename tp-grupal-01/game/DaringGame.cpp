#include "DaringGame.h"

#include <algorithm>
#include <ctime>
#include "../log/Log.h"

DaringGame::DaringGame(int numPlayers) :
	turnManager(numPlayers), player(turnManager), numPlayers(numPlayers) {
	shuffleCards();
    LOG_INFO("Juego inicializado con " + std::to_string(numPlayers) + " jugadores.");
}

DaringGame::~DaringGame() {}

int DaringGame::start(int id, Pipe& cardStream) {
	this->initialCards.clear();
	player.setId(id);
	receiveCards(cardStream);
	player.start(id);
	return 0;
}

void DaringGame::stop() {
	player.stop();
}

void DaringGame::receiveCards(Pipe& cardStream) {
	int numCards = 0;
	cardStream.read(&numCards, sizeof(int));

	std::vector<SerializedCard> newSerializedCards((unsigned long)numCards, Card::DefaultSerializedCard);
	cardStream.read(newSerializedCards.data(), sizeof(Card::DefaultSerializedCard) * numCards);
    std::vector<Card> newCards = Card::toCard(newSerializedCards);

	std::string cards;
	for (Card &card : newCards) {
		cards += "\n\t " + card.toString();
	}
	LOG_INFO("Jugador " + std::to_string(player.getId()) + std::string(" recibió ") + std::to_string(numCards) + " cartas");
	LOG_DEBUG("Player id: " + std::to_string(player.getId()) + "\n\tCartas recibidas:" + cards);

	player.addCards(newCards);
}

void DaringGame::sendCards(int id, Pipe& cardStream) {
	//Calculate Player index in cards
	int cardsToSend = (int)(this->initialCards.size() / this->numPlayers);
	if (id == (this->numPlayers - 1)) {
		cardsToSend += this->initialCards.size() % this->numPlayers;
	}
	int firstCard = (int)(this->initialCards.size() / this->numPlayers);
	firstCard *= id;

	//Serialize and send
	std::vector<SerializedCard> sInitialCards = Card::Serialize( this->initialCards );
	SerializedCard* cardBuff = &sInitialCards[firstCard];
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
	srand ( (unsigned int)time(NULL) );
	std::random_shuffle(this->initialCards.begin(), this->initialCards.end());
}

Table DaringGame::getTable() const {
    return player.getTable();
}

void DaringGame::free() {
	player.free();
	this->initialCards.clear();
}
