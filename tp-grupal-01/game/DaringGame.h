#ifndef DARINGGAME_H
#define DARINGGAME_H

#include <vector>
#include "TurnManager.h"
#include "Player.h"

class Card;

class DaringGame {
public:
	explicit DaringGame(int numPlayers);
	~DaringGame();
	int start(int id);
	void stop();
private:
    void dealCards();
	std::vector<Card> discardPile;
	TurnManager turnManager;
	Player player;
	Table table;
	int numPlayers;
	bool status;
};

#endif // DARINGGAME_H
