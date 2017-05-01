#include "SimpleAction.h"


SimpleAction::SimpleAction(const std::string& _name) : Action(_name.front()){
    name = _name;
}

SimpleAction::SimpleAction() : Action('s'){
    name = "Unnamed Simple Action";
}

std::string SimpleAction::getName() const{
    return name;
}

SimpleAction::~SimpleAction() {}