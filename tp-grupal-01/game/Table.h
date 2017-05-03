#ifndef CONCURRENTES_TABLE_H
#define CONCURRENTES_TABLE_H

#include <vector>
#include <map>
#include "Card.h"
#include "../util/SharedMemory.h"
#include "../util/Pipe.h"

class Table {
public:
    Table(int numPlayers);
    ~Table();

    Card getLastCard();
    Card getLastToLastCard();

    //retorna las cartas y las quita de la mesa.
    std::vector<Card> takeAllCards(int playerID);

    void pushCard(Card card,int playerID);

    int getNumberOfCards(int playerID);

    void setNumberOfCards(int playerID, int cant);

    bool putHandOnHeap(int playerID);

    /**
     * Si hay ganador retorna el ID, caso contrario -1
     */
    int winner();

    /*
     * Setea el ganador;
     */
    void winned(int playerID);

private:
    static const std::string tableFilename;

    //Last Card
    SharedMemory<char> lastCardRank;
    SharedMemory<CardSuit> lastCardSuit;

    //Last to Last Card
    SharedMemory<char> lastToLastCardRank;
    SharedMemory<CardSuit> lastToLastCardSuit;

    //Manos en el pilon de cartas
    SharedMemory<int> lastPlayerWithHandInHeap;
    SharedMemory<int> numPlayersWithHandInHeap;

    //Cantidad de cartas de cada jugador
    std::vector<SharedMemory<int>> playersNumberOfCards;

    //Pipe con las cartas en la mesa y cantidad en memoria compartida
    Pipe* cardsOnTable;
    SharedMemory<int> numCardsOnTable;

    SharedMemory<int> winnerPlayerID;
};


#endif //CONCURRENTES_TABLE_H
