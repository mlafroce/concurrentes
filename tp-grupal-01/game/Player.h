#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Card.h"
#include "Table.h"
#include "../util/SharedMemory.h"

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
	//SharedMemory<int> getNumberOfCards;
	Table table;
	TurnManager& turnManager;
	char id;
	bool running;
};

#endif // PLAYER_H
