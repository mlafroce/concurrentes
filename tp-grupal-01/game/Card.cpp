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
	result << (int) rank << " de ";
	switch(this->suit) {
		case A:
			result << " basto";
			break;
		case B:
			result << " copas";
			break;
		case C:
			result << " espadas";
			break;
		case D:
			result << " oro";
			break;
	}
	return result.str();
}
