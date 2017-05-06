#ifndef CARD_H
#define CARD_H

#include <string>
#include <vector>

enum CardSuit {A, B, C, D};

struct SerializedCard {
	CardSuit suit;
	char rank;
};

class Card {
public:
	/**
	 * Constructor
	 */
	Card(CardSuit suit, char rank);
	char getRank() const;
    int getNumber() const;
    CardSuit getSuite() const;

	static const char MaxCardRank;
	static const Card DefaultCard;
	static const SerializedCard DefaultSerializedCard;
	static Card toCard(const SerializedCard &sCard);
	static std::vector<Card> toCard( const std::vector<SerializedCard> &sCards );
	static SerializedCard Serialize(const Card &sCard);
	static std::vector<SerializedCard> Serialize( const std::vector<Card> &sCards );

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
