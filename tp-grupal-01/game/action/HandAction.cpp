#include "HandAction.h"

HandAction::HandAction(int _numberOfHands) : Action('h'),numberOfHands(_numberOfHands) {}

int HandAction::getWinnerId() const {
    return this->getFirstId();
}

int HandAction::getLooserId() const {
    return this->getLastId();
}

bool HandAction::allHandsPlayed() const {
    return (this->count() == numberOfHands);
}