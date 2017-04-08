#ifndef CARD_H
#define CARD_H

enum CardSuit {A, B, C, D};

class Card {
public:
	Card(CardSuit suit, char rank);
	char getRank();
	static const char MaxCardRank;
private:
	CardSuit suit;
	char rank;
};

#endif // CARD_H
