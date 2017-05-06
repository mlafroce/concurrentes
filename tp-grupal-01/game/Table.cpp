#include "Table.h"

#include <cstring>
#include <iostream>

#define FILE_IPCS "tableinformation.semaphore.ipc"

const std::string Table::tableFilename("table.ipc");

Table::Table(int numPlayers) : lastCard(tableFilename,'l'),
                               lastToLastCard(tableFilename,'m'),
                               numCardsOnTable(tableFilename,'n'),cardsOnTable(new Pipe()),
                               winnerPlayerID(tableFilename,'w'),
                               mutexTableInformation(FILE_IPCS,'s',1){
    for (int i = 0; i < numPlayers ; ++i) {
        playersNumberOfCards.push_back(SharedMemory<int>(tableFilename,(char)i));
    }
    mutexTableInformation.wait();
        lastCard.write(Card::DefaultSerializedCard);
        winnerPlayerID.write(-1);
    mutexTableInformation.signal();
    numCardsOnTable.write(0);
    lastToLastCard.write(Card::DefaultSerializedCard);
}

Card Table::getLastCard() {
    return Card::toCard(lastCard.read());
}

std::vector<Card> Table::takeAllCards(int playerID) {
    int cantCards = numCardsOnTable.read();

    std::vector<SerializedCard> sCards((unsigned long)cantCards, Card::DefaultSerializedCard);
    cardsOnTable->read(sCards.data(), sizeof(Card::DefaultSerializedCard) * cantCards);
    numCardsOnTable.write(0);

    std::vector<Card> cards = Card::toCard(sCards);

    this->setNumberOfCards(playerID,(int)(playersNumberOfCards[playerID].read() + cards.size()));

    return cards;
}

void Table::pushCard(Card card,int playerID) {
    mutexTableInformation.wait();
        SerializedCard sCard = Card::Serialize(card);
        cardsOnTable->write(&sCard,sizeof(sCard));
        numCardsOnTable.write(numCardsOnTable.read() + 1);
        lastToLastCard.write( lastCard.read() );
        lastCard.write(Card::Serialize(card));
    mutexTableInformation.signal();


    this->setNumberOfCards(playerID,playersNumberOfCards[playerID].read() - 1);
}

int Table::getNumberOfCards(int playerID) {
    return playersNumberOfCards[playerID].read();
}

void Table::setNumberOfCards(int playerID, int cant) {
    SharedMemory<int> shmem = playersNumberOfCards[playerID];
    mutexTableInformation.wait();
        shmem.write(cant);
    mutexTableInformation.signal();
}

Table::~Table() {
}

Card Table::getLastToLastCard() {
    return Card::toCard( lastToLastCard.read() );
}

int Table::winner() {
    return winnerPlayerID.read();
}

void Table::winned(int playerID) {
    if (winnerPlayerID.read() < 0){
        mutexTableInformation.wait();
            winnerPlayerID.write(playerID);
        mutexTableInformation.signal();
    }
}

std::map<std::string,int> Table::stats() {
    std::map<std::string,int> stats;

    mutexTableInformation.wait();
        for (int i = 0; i < playersNumberOfCards.size(); ++i) {
            stats[std::to_string(i)] = this->getNumberOfCards(i);
        }
        int winner = winnerPlayerID.read();
    mutexTableInformation.signal();

    if (winner >= 0){
        stats["winner"] = winner;
    }

    return stats;
}

void Table::free() {
    delete cardsOnTable;
    mutexTableInformation.Delete();
}


