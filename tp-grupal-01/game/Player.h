#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Card.h"

class TurnManager;

class Player {
public:
	Player(TurnManager& turnManager);
	void start(int id);
	void stop();
	void processCard();
	void playCard();
	char getId() const;
private:
	std::vector<Card> cards;
	TurnManager& turnManager;
	char id;
	bool running;
};

#endif // PLAYER_H
