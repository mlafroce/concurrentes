#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "../util/Thread.h"
#include "Card.h"

class TurnManager;

class Player : public Thread {
public:
	Player(char playerId, TurnManager& turnManager);
	virtual void run();
	void stop();
	void take(const Card& card);
	char getId() const;
private:
	std::vector<Card> cards;
	TurnManager& turnManager;
	char id;
	bool running;
};

#endif // PLAYER_H
