#include "Player.h"


#include "TurnManager.h"
#include "../log/Log.h"
#include "action/SimpleAction.h"
#include "action/HandAction.h"


Player::Player(TurnManager& turnManager) :
	turnManager(turnManager), running(false),table(Table(turnManager.getNumberPlayers())){}

void Player::start(int id) {
	this->id = id;
	this->running = true;
	LOG_INFO("Iniciando la mesa del jugador " + std::to_string(this->id));
    table.setNumberOfCards(this->getId(), (int) cards.size());
    play();
}

void Player::stop() {
	this->running = false;
}

void Player::play() {
	LOG_INFO("Arrancando el jugador " + std::to_string(this->id));
	while (this->running) {
        turnManager.waitToTurnBegin();
        if (table.winner() >= 0){
            stop();
            continue;
        }
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
    table.pushCard(card,this->getId());
    LOG_INFO("El jugador " + std::to_string(this->id) + " jugó " + card.toString() );
}

void Player::processCard() {
    Card lastCard = table.getLastCard();
    Card lastToLastCard = table.getLastToLastCard();


    //4.Si la carta es un 7, entonces todos los jugadores dicen en voz alta “Atrevido” y colocan su mano
    //  sobre el piĺón que est́a en el centro de la mesa. El  ́ultimo jugador en poner la mano toma todas
    //  las cartas del piĺon central y las agrega al suyo, poníendolas boca abajo.
    //5.Si la carta es del mismo numero que la carta anterior, entonces todos los jugadores colocan su
    //  mano sobre el pilon (misma mecanica que cuando sale un 7).
    if (lastCard.getNumber() == lastToLastCard.getNumber() || lastCard.getNumber() == 7){
        doHandAction();
    } else {
        switch (lastCard.getNumber()) {

            //1.  Si la carta es un 10, entonces todos los jugadores dicen en voz alta “Buenos d́ıas sẽnorita”.
            case 10:
                say("Buenos días señorita");
                break;

            //2.  Si la carta es un 11, entonces todos los jugadores dicen en voz alta “Buenas noches caballero”.
            case 11:
                say("Buenas noches caballero");
                break;

            //3.  Si la carta es un 12, entonces todos los jugadores hacen la venia (saludo militar).
            case 12:
                venia();
                break;

            default:
                LOG_INFO("El jugador " + std::to_string(getId()) + " no genera acción inmediata ya que la carta es un " + std::to_string(lastCard.getNumber()));
                break;
        }
    }


    checkNumberOfCards();
}

void Player::doHandAction() {
    std::string message = "El jugador " + std::to_string(this->id);

    SimpleAction sayAction("Atrevido!");
    sayAction.doAction(this->id);
    LOG_INFO(message + " dijo: \"Atrevido!\"");

    HandAction handAction(this->turnManager.getNumberPlayers());
    handAction.doAction(this->id);
    LOG_INFO(message + " puso la mano sobre la mesa");

    turnManager.waitToDoAction();

    if (handAction.allHandsPlayed() && handAction.getLastId() == this->id) {
        LOG_INFO(message + " fue el ultimo en poner la mano sobre la mesa. Se lleva la pila de descarte");
        takeCardsOnTable();
    }
}

void Player::say(std::string phrase){
    SimpleAction sayAction(phrase);
    sayAction.doAction(this->id);
    LOG_INFO("El jugador " + std::to_string(this->id) + " dijo: \"" + phrase +  "\"");
    this->turnManager.waitToDoAction();
    if (sayAction.getLastId() == this->id) {
        LOG_INFO("Todos los jugadores hicieron \"" + phrase + "\". El último es jugador " + std::to_string(this->id) );
    }
}

void Player::venia() {
    this->say("Venia");
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
    LOG_INFO("El jugador " + std::to_string(this->id) + " tomó todas ("+ std::to_string(cards.size()) +") las cartas de la mesa" );
}

void Player::checkNumberOfCards() {
    if (this->cards.empty()){
        LOG_INFO("El jugador " + std::to_string(this->id) + " se quedó sin cartas. GANÓ!!!" );
        table.winned(this->getId());
    }
}

Table Player::getTable() const {
    return this->table;
}

void Player::setId(const int ID) {
    this->id = ID;
}

void Player::free() {
    table.free();
}
