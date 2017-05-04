#ifndef TURNMANAGER_H
#define TURNMANAGER_H

#include <vector>
#include "../util/BarrierSimple.h"
#include "../util/SharedMemory.h"

class Player;

class TurnManager {
public:
	explicit TurnManager(int numPlayers);
	/**
	 * Devuelve true si el contador de turnos corresponde al id del jugador
	 */
	bool isMyTurn(const Player& player);
	/**
	 * Avanza el contador de turnos
	 */
	void passTurn();
	/**
	 * Activa la barrera previa a jugar el turno
	 */
	void waitToTurnBegin();
	/**
	 * Activa la barrera entre previa a procesar la carta jugada
	 */
	void waitToProcessCard();

	/**
	 * Activa la barrera para realizar accion.
	 */
	void waitToDoAction();

	/**
	 * Destraba las barreras
	 */
	void freeBarriers();

	void freeActionBarrier();

    int getNumberPlayers();
private:
	static const std::string barrierFilename;
	static const std::string sharedMemoryFilename;
	int numPlayers;
	SharedMemory<int> turnCounter;
	BarrierSimple barTurnBegin;
	BarrierSimple barProcessCard;
	BarrierSimple barAction;
};

#endif // TURNMANAGER_H
