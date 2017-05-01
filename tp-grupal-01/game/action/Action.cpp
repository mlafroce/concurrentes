#include "Action.h"

#define FILE "README.md"

Action::Action(char actionID) {
    callsActions = new SharedMemory<std::list<int>>(FILE,actionID);
}

Action::~Action() {
    delete callsActions;
}

int Action::count() const {
    return (int)callsActions->read().size();
}

void Action::doAction(const int id) {
    std::list<int> listActions = callsActions->read();
    listActions.push_back(id);
    callsActions->write(listActions);
}

int Action::getFirstId() const {
    if (this->isEmpty()) {
        return -1;
    }
    return (int)callsActions->read().front();
}

int Action::getLastId() const {
    if (this->isEmpty()) {
        return -1;
    }
    return (int)callsActions->read().back();
}

bool Action::isEmpty() const {
    return (this->count() == 0);
}

bool Action::didAction(const int id) {
    std::list<int> actions = callsActions->read();
    for (int& actionId : actions) {
        if (actionId == id) {
            return true;
        }
    }
    return false;
}

int Action::getIdPosition(int id) {
    std::list<int> actions = callsActions->read();
    int position = 0;
    for (int& actionId : actions) {
        if (actionId == id) {
            return position;
        }
        position++;
    }
    return -1;
}