//
// Created by facu on 01/05/17.
//

#include "Table.h"

Table::Table() : cardsOnTheTable(FILE, 'c'), playersNumberOfCards(FILE, 'n'){
    cardsOnTheTable.write(std::vector<Card>());
    playersNumberOfCards.write(std::map<char,int>());
}

Card Table::getLastCard() {
    return cardsOnTheTable.read()[-1];
}

std::vector<Card> Table::takeAllCards(char playerID) {
    std::vector<Card> cards = cardsOnTheTable.read();
    cardsOnTheTable.write(std::vector<Card>());

    std::map<char,int> mapPlayers = playersNumberOfCards.read();
    if (mapPlayers.find(playerID) != mapPlayers.end()){
        mapPlayers[playerID] += cards.size();
        playersNumberOfCards.write(mapPlayers);
    }

    return cards;
}

void Table::pushCard(Card card,char playerID) {
    std::vector<Card> cards = cardsOnTheTable.read();
    cards.push_back(card);
    cardsOnTheTable.write(cards);

    std::map<char,int> mapPlayers = playersNumberOfCards.read();
    if (mapPlayers.find(playerID) != mapPlayers.end()){
        mapPlayers[playerID]--;
        playersNumberOfCards.write(mapPlayers);
    }
}

int Table::getNumberOfCards(char playerID) {
    std::map<char,int> mapPlayers = playersNumberOfCards.read();
    if (mapPlayers.find(playerID) != mapPlayers.end()){
        return mapPlayers[playerID];
    }

    return -1;
}

void Table::setNumberOfCards(char playerID, int cant) {
    std::map<char,int> mapPlayers = playersNumberOfCards.read();
    mapPlayers[playerID] = cant;
    playersNumberOfCards.write(mapPlayers);
}

Table::~Table() {
    //delete(playersNumberOfCards);
    //delete(cardsOnTheTable);
}


