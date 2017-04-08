#ifndef PLAYER_H
#define PLAYER_H

#include "../util/Thread.h"

class Player : public Thread {
public:
	Player(char playerId);
	virtual void run();
	void stop();
private:
	char id;
	bool running;
};

#endif // PLAYER_H
