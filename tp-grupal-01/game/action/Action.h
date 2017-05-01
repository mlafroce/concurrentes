#ifndef CONCURRENTES_ACTION_H
#define CONCURRENTES_ACTION_H

#include "../../util/SharedMemory.h"
#include <list>

class Action {
private:
    SharedMemory<std::list<int>> *callsActions;

public:
    Action(const char actionID);
    ~Action();


    void doAction(const int id);

    int getFirstId() const;
    int getLastId() const;
    bool isEmpty() const;
    int count() const;

    bool didAction(int id);
    int getIdPosition(int id);


};


#endif //CONCURRENTES_ACTION_H
