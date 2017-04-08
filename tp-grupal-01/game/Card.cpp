#include "Card.h"

const char Card::MaxCardRank = 12;

Card::Card(CardSuit suit, char rank) :
	suit(suit), rank(rank){}
