#include "SimpleAction.h"
#include "../../Log/Log.h"


SimpleAction::SimpleAction(const std::string& _name) : Action(_name.front()){
    name = _name;
    if (name.front() == 'h') {
        LOG_WARNING("El nombre de la accion puede causar errores ya que su primera letra 'h' esta reservada para HandAciton");
    }
}

SimpleAction::SimpleAction() : Action('s'){
    name = "Unnamed Simple Action";
}

std::string SimpleAction::getName() const{
    return name;
}

SimpleAction::~SimpleAction() {}