#ifndef CARD_H
#define CARD_H
#include <string>

enum CardSuit {A, B, C, D};

class Card {
public:
	/**
	 * Constructor
	 */
	Card(CardSuit suit, char rank);
	char getRank() const;
    CardSuit getSuite() const;
	static const char MaxCardRank;
	std::string toString() const;
	bool operator==(Card& otherCard)const {
		if (this->rank < 0 || otherCard.getRank() < 0){
			return false;
		}
		return (this->rank == otherCard.getRank()) and (this->suit == otherCard.getSuite());
	}

private:
	CardSuit suit;
	char rank;
};

#endif // CARD_H
