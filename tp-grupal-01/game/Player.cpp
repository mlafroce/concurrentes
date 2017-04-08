#include "Player.h"
#include <cstdio>
#include <unistd.h>

Player::Player(char playerId) : 
	Thread(), id(playerId), running(false){}

void Player::run() {
	this->running = true;
	while (this->running) {
		printf("Soy el jugador %d\n", this->id);
		sleep(1);
	}
	printf("Listo para join%d\n", this->id);
}

void Player::stop() {
	printf("Jugador[%d]->stop()\n", this->id);
	this->running = false;
}