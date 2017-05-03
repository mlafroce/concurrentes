#include "Card.h"
#include <sstream>

const char Card::MaxCardRank = 12;

Card::Card(CardSuit suit, char rank) :
	suit(suit), rank(rank){}

char Card::getRank() const {
	return rank;
}

std::string Card::toString() const {
	std::stringstream result;
	result << (rank + 1) << " de";
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
