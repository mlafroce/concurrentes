#include "Card.h"
#include <sstream>

const char Card::MaxCardRank = 12;
const Card Card::DefaultCard(A,0);
const SerializedCard Card::DefaultSerializedCard{A,0};

Card::Card(CardSuit suit, char rank) :
	suit(suit), rank(rank){}

char Card::getRank() const {
	return rank;
}

std::string Card::toString() const {
	std::stringstream result;
	result << std::to_string(rank) << " de";
	switch(this->suit) {
		case A:
			result << " Basto";
			break;
		case B:
			result << " Copas";
			break;
		case C:
			result << " Espadas";
			break;
		case D:
			result << " Oro";
			break;
	}
	return result.str();
}

CardSuit Card::getSuite() const {
	return this->suit;
}

int Card::getNumber() const {
	return (int)rank;
}

Card Card::toCard(const SerializedCard& sCard) {
	return Card{sCard.suit, sCard.rank};
}

std::vector<Card> Card::toCard( const std::vector<SerializedCard> &sCards ) {
	std::vector<Card> cards;
	for (SerializedCard sCard : sCards) {
		cards.push_back( Card::toCard(sCard) );
	}
	return cards;
}

SerializedCard Card::Serialize(const Card& card) {
	return SerializedCard{card.getSuite(), card.getRank()};
}

std::vector<SerializedCard> Card::Serialize( const std::vector<Card> &cards ) {
	std::vector<SerializedCard> sCards;
	for (Card card : cards) {
		sCards.push_back( Card::Serialize(card) );
	}
	return sCards;
}
