#ifndef TURNMANAGER_H
#define TURNMANAGER_H

#include <vector>
#include "../util/BarrierSimple.h"

class Player;

class TurnManager {
public:
	explicit TurnManager(const std::vector<Player>& players);
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
	 * Destraba las barreras
	 */
	void freeBarriers();
private:
	int numPlayers;
	int turnCounter;
	BarrierSimple barTurnBegin;
	BarrierSimple barProcessCard;
};

#endif // TURNMANAGER_H
