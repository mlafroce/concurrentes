#ifndef CONCURRENTES_TABLE_H
#define CONCURRENTES_TABLE_H

#include <vector>
#include <map>
#include "Card.h"
#include "../util/SharedMemory.h"

#define FILE "README.md"

class Table {
public:
    Table();
    ~Table();
    Card getLastCard();

    //retorna las cartas y las quita de la mesa.
    std::vector<Card> takeAllCards(char playerID);

    void pushCard(Card card,char playerID);

    int getNumberOfCards(char playerID);

    void setNumberOfCards(char playerID, int cant);

private:
    SharedMemory<std::vector<Card>> cardsOnTheTable;
    SharedMemory<std::map<char,int>> playersNumberOfCards;
};


#endif //CONCURRENTES_TABLE_H
