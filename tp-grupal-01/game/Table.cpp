#include "Table.h"

const std::string Table::tableFilename("/bin/bash");

Table::Table() : cardsOnTheTable(tableFilename, 'c'), playersNumberOfCards(tableFilename, 'n'){
    cardsOnTheTable.write(new std::vector<Card>());
    playersNumberOfCards.write( new std::map<char,int>());
}

Card Table::getLastCard() {
    std::vector<Card> cards = *cardsOnTheTable.read();
    return cards[-1];
}

std::vector<Card> Table::takeAllCards(char playerID) {
    std::vector<Card> cards = *cardsOnTheTable.read();
    cardsOnTheTable.write(new std::vector<Card>());

    std::map<char,int> mapPlayers = *playersNumberOfCards.read();
    if (mapPlayers.find(playerID) != mapPlayers.end()){
        mapPlayers[playerID] += cards.size();
        playersNumberOfCards.write(&mapPlayers);
    }

    return cards;
}

void Table::pushCard(Card card,char playerID) {
    std::vector<Card> cards = *cardsOnTheTable.read();
    cards.push_back(card);
    cardsOnTheTable.write(&cards);

    std::map<char,int> mapPlayers = *playersNumberOfCards.read();
    if (mapPlayers.find(playerID) != mapPlayers.end()){
        mapPlayers[playerID] -= 1;
        playersNumberOfCards.write(&mapPlayers);
    }
}

int Table::getNumberOfCards(char playerID) {
    std::map<char,int> mapPlayers = *playersNumberOfCards.read();
    if (mapPlayers.find(playerID) != mapPlayers.end()){
        return mapPlayers[playerID];
    }

    return -1;
}

void Table::setNumberOfCards(char playerID, int cant) {
    std::map<char,int> mapPlayers = *playersNumberOfCards.read();
    mapPlayers[playerID] = cant;
    playersNumberOfCards.write(&mapPlayers);
}

Table::~Table() {
    //delete(playersNumberOfCards);
    //delete(cardsOnTheTable);
}


