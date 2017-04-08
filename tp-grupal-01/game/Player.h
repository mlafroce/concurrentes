#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "../util/Thread.h"
#include "Card.h"

class Player : public Thread {
public:
	Player(char playerId);
	virtual void run();
	void stop();
	void take(const Card& card);
private:
	std::vector<Card> cards;
	char id;
	bool running;
};

#endif // PLAYER_H
