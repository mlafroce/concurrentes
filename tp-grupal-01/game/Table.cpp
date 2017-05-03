#include <cstring>
#include <iostream>
#include "Table.h"
#include "../log/Log.h"

const std::string Table::tableFilename("DaringGame.log");

Table::Table(int numPlayers) : lastCardSuit(tableFilename,'s'),lastCardRank(tableFilename,'r'),
                               lastToLastCardSuit(tableFilename,'a'),lastToLastCardRank(tableFilename,'l'),
                               numCardsOnTable(tableFilename,'n'),cardsOnTable(new Pipe()),
                               lastPlayerWithHandInHeap(tableFilename,'p'),numPlayersWithHandInHeap(tableFilename,'m'){
    for (int i = 0; i < numPlayers ; ++i) {
        playersNumberOfCards.push_back(SharedMemory<int>(tableFilename,i));
    }
    lastCardRank.write(-1);
    lastCardSuit.write(A);
    numCardsOnTable.write(0);
    lastToLastCardRank.write(-1);
    lastToLastCardSuit.write(A);
    lastPlayerWithHandInHeap.write(-1);
    numPlayersWithHandInHeap.write(0);
}

Card Table::getLastCard() {
    return Card(lastCardSuit.read(),lastCardRank.read());
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

    CardSuit suite = lastCardSuit.read();
    int rank = lastCardRank.read();

    lastCardRank.write(card.getRank());
    lastCardSuit.write(card.getSuite());

    lastToLastCardRank.write(rank);
    lastToLastCardSuit.write(suite);

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

Card Table::getLastToLastCard() {
    return Card(lastToLastCardSuit.read(),lastToLastCardRank.read());
}

bool Table::putHandOnHeap(int playerID) {
    lastPlayerWithHandInHeap.write(playerID);
    int cantPlayers = numPlayersWithHandInHeap.read();
    numPlayersWithHandInHeap.write(cantPlayers + 1);

    LOG_INFO(std::to_string(cantPlayers) + " pusieron la mano en el pilón.");

    //si la cantidad de juadores con mano en el pilon es igual a la cantidad de jugadores es por que es el ultimo.
    if (cantPlayers == playersNumberOfCards.size()){
        LOG_INFO("El jugador " + std::to_string(playerID) + " fue el último en poner la mano en el pilón.");
        numPlayersWithHandInHeap.write(0);
        return true;
    }

    return false;
}


