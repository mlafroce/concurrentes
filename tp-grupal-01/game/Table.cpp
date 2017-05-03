#include <cstring>
#include <iostream>
#include "Table.h"

const std::string Table::tableFilename("DaringGame.log");

Table::Table(int numPlayers) : lasCardSuit(tableFilename,'s'),lastCardRank(tableFilename,'r'),numCardsOnTable(tableFilename,'n'),cardsOnTable(new Pipe()) {
    for (int i = 0; i < numPlayers ; ++i) {
        playersNumberOfCards.push_back(SharedMemory<int>(tableFilename,i));
    }
    lastCardRank.write(-1);
    lasCardSuit.write(A);
    numCardsOnTable.write(0);
}

Card Table::getLastCard() {
    return Card(lasCardSuit.read(),lastCardRank.read());
}

std::vector<Card> Table::takeAllCards(int playerID) {
    int cantCards = numCardsOnTable.read();
    Card defaultCard(A, 0);
    std::vector<Card> cards(cantCards, defaultCard);
    cardsOnTable->read(cards.data(), sizeof(defaultCard) * cantCards);
    numCardsOnTable.write(0);

    SharedMemory<int> shmem = playersNumberOfCards[playerID];
    int numCards = shmem.read();
    numCards += cards.size();
    shmem.write(numCards);

    return cards;
}

void Table::pushCard(Card card,int playerID) {
    cardsOnTable->write(&card,sizeof(card));
    numCardsOnTable.write(numCardsOnTable.read()+1);

    lastCardRank.write(card.getRank());
    lasCardSuit.write(card.getSuite());

    SharedMemory<int> shmem = playersNumberOfCards[playerID];
    int numCards = shmem.read();
    numCards -=1;
    shmem.write(numCards);
}

int Table::getNumberOfCards(int playerID) {
    return playersNumberOfCards[playerID].read();
}

void Table::setNumberOfCards(int playerID, int cant) {
    SharedMemory<int> shmem = playersNumberOfCards[playerID];
    shmem.write(cant);
}

Table::~Table() {
    //delete(playersNumberOfCards);
    //delete(cardsOnTheTable);
}


