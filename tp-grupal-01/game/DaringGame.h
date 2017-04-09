#ifndef DARINGGAME_H
#define DARINGGAME_H

#include <vector>
#include "TurnManager.h"

class Card;
class Player;

class DaringGame
{
public:
	explicit DaringGame(int numPlayers);
	~DaringGame();
	void start();
	void stop();
private:
    void dealCards();
	std::vector<Card> discardPile;
	std::vector<Player> playerList;
	TurnManager turnManager;
	int numPlayers;
	bool status;
};

#endif // DARINGGAME_H
