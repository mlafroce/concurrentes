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
	/**
	 * Inicializa algunos atributos y arranca el juego
	 */
	void start(int id);
	/**
	 * Termina el loop principal
	 */
	void stop();
	/**
	 * Inspecciona la carta sobre la mesa
	 */
	void processCard();
	/**
	 * Toma una carta de la pila propia y la pone sobre la mesa
	 */
	void playCard();
	/**
	 * 
	 */
	void addCards(const std::vector<Card>& cards);
	/**
	 * identificador del jugador
	 */
	int getId() const;

    void say(std::string phrase);

    void venia();

    /**
	 * Pone la mano en la pila y retorna true si es el ultimo
	 */
    bool putHandOnHeap();
private:
	/**
	 * Loop principal
	 */
	void play();
	/**
	 * Mano propia
	 */
	std::vector<Card> cards;

    /**
     * Clase donde estan las cartas y datos compartidos
     */
    Table table;

    void takeCardsOnTable();

    /**
	 * Clase auxiliar que lo comunica con otros mecanismos de IPC
	 */
	TurnManager& turnManager;
	int id;
	bool running;
};

#endif // PLAYER_H
