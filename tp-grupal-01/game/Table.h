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

    //retorna las cartas y las quita de la mesa.
    std::vector<Card> takeAllCards(int playerID);

    void pushCard(Card card,int playerID);

    int getNumberOfCards(int playerID);

    void setNumberOfCards(int playerID, int cant);

private:
    static const std::string tableFilename;
    SharedMemory<char> lastCardRank;
    SharedMemory<CardSuit> lasCardSuit;
    std::vector<SharedMemory<int>> playersNumberOfCards;
    Pipe* cardsOnTable;
    SharedMemory<int> numCardsOnTable;
};


#endif //CONCURRENTES_TABLE_H
