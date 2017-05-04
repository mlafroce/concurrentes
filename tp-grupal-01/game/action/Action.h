#ifndef CONCURRENTES_ACTION_H
#define CONCURRENTES_ACTION_H

#include "../../util/SharedMemory.h"
#include "../../util/LockFile.h"
#include "../../util/Semaphore.h"
#include <vector>


class Action {
private:
    SharedMemory<int> *callsActions;
    LockFile* lockFile;
    Semaphore mutexSharedMemory;

    std::vector<int> getVector() const;
    std::string readFile() const;
    void writeInLock(const std::string& text);

    char actionID;
    std::string temporalFileName;

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

    void end();


};


#endif //CONCURRENTES_ACTION_H
