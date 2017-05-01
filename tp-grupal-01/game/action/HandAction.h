#ifndef CONCURRENTES_HANDACTION_H
#define CONCURRENTES_HANDACTION_H


#include "Action.h"

class HandAction : Action {
private:
    int numberOfHands;
public:
    HandAction(int _numberOfHands);
    ~HandAction(){};

    int getWinnerId() const;
    int getLooserId() const;

    bool allHandsPlayed() const;

};


#endif //CONCURRENTES_HANDACTION_H
