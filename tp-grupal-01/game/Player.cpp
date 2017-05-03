#include "Player.h"
#include <cstdio>
#include <vector>
#include <unistd.h>

#include "TurnManager.h"
#include "../Log/Log.h"


Player::Player(TurnManager& turnManager) :
	turnManager(turnManager), running(false),table(Table(turnManager.getNumberPlayers())){}

void Player::start(int id) {
	this->id = id;
	this->running = true;
	LOG_INFO("Iniciando la mesa del jugador " + std::string(1, 48 + this->id));
    table.setNumberOfCards(this->getId(), (int) cards.size());
	play();
}

void Player::stop() {
	this->running = false;
}

void Player::play() {
	LOG_INFO("Arrancando el jugador " + std::string(1, 48 + this->id));
	while (this->running) {
		turnManager.waitToTurnBegin();
		if (this->turnManager.isMyTurn(*this)) {
			playCard();
			turnManager.waitToProcessCard();
			this->turnManager.passTurn();
		} else {
			turnManager.waitToProcessCard();
		}
		processCard();
	}
	// Destrabo barreras 
	turnManager.freeBarriers();
}


void Player::playCard() {
	Card card = this->cards.back();
	this->cards.pop_back();
	LOG_INFO("El jugador " + std::string(1, 48 + this->id)
	+ " jugó " + card.toString() );
    table.pushCard(card,this->getId());
}

void Player::processCard() {
    Card lastCard = table.getLastCard();
    Card lastToLastCard = table.getLastToLastCard();

    LOG_INFO("El jugador " + std::string(1, 48 + this->id) + " procesara " + lastCard.toString() );

    //sleep(1);

    switch (lastCard.getRank()) {

        //1.  Si la carta es un 10, entonces todos los jugadores dicen en voz alta “Buenos d́ıas sẽnorita”.
        case char(10):
            say("Buenos días señorita");
            break;

        //2.  Si la carta es un 11, entonces todos los jugadores dicen en voz alta “Buenas noches caballero”.
        case char(11):
            say("Buenas noches caballero");
            break;

        //3.  Si la carta es un 12, entonces todos los jugadores hacen la venia (saludo militar).
        case char(12):
            venia();
            break;

        //4.  Si la carta es un 7, entonces todos los jugadores dicen en voz alta “Atrevido” y colocan su mano
        //sobre el piĺón que est́a en el centro de la mesa. El  ́ultimo jugador en poner la mano toma todas
        //las cartas del piĺon central y las agrega al suyo, poníendolas boca abajo.
        case char(7):
            say("Atrevido");
            if(putHandOnHeap()){
                takeCardsOnTable();
            }
            break;

        default:break;
    }

    //5.  Si la carta es del mismo numero que la carta anterior, entonces todos los jugadores colocan su
    //mano sobre el pilon (misma mecanica que cuando sale un 7).
    if (lastCard == lastToLastCard){
        if(putHandOnHeap()){
            takeCardsOnTable();
        }
    }


}

void Player::say(std::string phrase){
    LOG_INFO("El jugador " + std::string(1, 48 + this->id) + " dijo " + phrase );
}

void Player::venia() {
    LOG_INFO("El jugador " + std::string(1, 48 + this->id) + " hizo la venia" );
}

bool Player::putHandOnHeap(){
    LOG_INFO("El jugador " + std::string(1, 48 + this->id) + " puso la mano en la pila" );
    //TODO
    if (this->getId() == 0){
        return true;
    }
    return false;
}

void Player::addCards(const std::vector<Card>& cards) {
	this->cards.insert(this->cards.end(), cards.begin(), cards.end());
}


int Player::getId() const {
	return this->id;
}

void Player::takeCardsOnTable() {
    std::vector<Card> cards = table.takeAllCards(this->getId());
    this->addCards(cards);
    LOG_INFO("El jugador " + std::string(1, 48 + this->id) + " tomó todas ("+ std::to_string(cards.size()) +") las cartas de la mesa" );
}
