#ifndef DARINGGAME_H
#define DARINGGAME_H

#include <vector>
#include "TurnManager.h"
#include "Player.h"

class Card;
class Pipe;

class DaringGame {
public:
	explicit DaringGame(int numPlayers);
	~DaringGame();
	/**
	 * Inicializa el jugador
	 */
	int start(int id, Pipe& cardStream);
	void stop();
	/**
	 * Recibe cartas por el pipe
	 */
	void receiveCards(Pipe& cardPipe);
	/**
	 * Envia cartas por el pipe
	 */
	void sendCards(int id, Pipe& cardPipe);

	Table getTable() const;
private:
    void shuffleCards();
	std::vector<Card> initialCards;
	TurnManager turnManager;
	Player player;
	int numPlayers;
	bool status;
};

#endif // DARINGGAME_H
