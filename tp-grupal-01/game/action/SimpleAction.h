#ifndef CONCURRENTES_SIMPLEACTION_H
#define CONCURRENTES_SIMPLEACTION_H


//
//  Like `Buenos dias Senorita`, `Buenas noches caballero`, `venia`, `Atrevido`
//

#include "Action.h"
#include <string>

class SimpleAction : Action {
private:
    std::string name;
public:
    SimpleAction(const std::string& name);
    SimpleAction();
    ~SimpleAction();

    std::string getName() const;

};


#endif //CONCURRENTES_SIMPLEACTION_H
