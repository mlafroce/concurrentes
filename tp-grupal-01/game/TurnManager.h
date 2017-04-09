#ifndef TURNMANAGER_H
#define TURNMANAGER_H

#include <vector>
#include "../util/Semaphore.h"

class Player;

class TurnManager {
public:
	explicit TurnManager(const std::vector<Player>& players);
	/**
	 * Decrementa el semaforo asociado al jugador.
	 */
	void wait(const Player& player);
	/**
	 * Despierta a todos los jugadores
	 */
	void signalAll();
	/**
	 * Busca el jugador siguiente a @param player y lo despierta
	 */
	void signalNext(const Player& player);
private:
	std::vector<Semaphore> semaphores;
};

#endif // TURNMANAGER_H
