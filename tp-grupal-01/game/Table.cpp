#include "Table.h"

#include <cstring>
#include <iostream>

const std::string Table::tableFilename("table.ipc");

Table::Table(int numPlayers) : lastCardSuit(tableFilename,'s'),lastCardRank(tableFilename,'r'),
                               lastToLastCardSuit(tableFilename,'a'),lastToLastCardRank(tableFilename,'l'),
                               numCardsOnTable(tableFilename,'n'),cardsOnTable(new Pipe()),
                               lastPlayerWithHandInHeap(tableFilename,'p'),numPlayersWithHandInHeap(tableFilename,'m'),
                               winnerPlayerID(tableFilename,'w'){
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
    winnerPlayerID.write(-1);
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
}

Card Table::getLastToLastCard() {
    return Card(lastToLastCardSuit.read(),lastToLastCardRank.read());
}

int Table::winner() {
    return winnerPlayerID.read();
}

void Table::winned(int playerID) {
    if (winnerPlayerID.read() < 0){
        winnerPlayerID.write(playerID);
    }
}

std::map<std::string,int> Table::stats() {
    std::map<std::string,int> stats;
    for (int i = 0; i < playersNumberOfCards.size(); ++i) {
        stats[std::to_string(i)] = this->getNumberOfCards(i);
    }
    int winner = winnerPlayerID.read();
    if (winner >= 0){
        stats["winner"] = winner;
    }

    return stats;
}


