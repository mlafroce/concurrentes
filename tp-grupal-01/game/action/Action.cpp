#include <cstring>
#include <fstream>
#include "Action.h"

#include "../../Log/Log.h"
//#include "../../util/Semaphore.h"

#define FILE "/bin/bash"
#define FILE_LOCK ".tmp.action"
#define ACTION_ID_SEPARATOR "::"

Action::Action(const char id) : actionID(id) {
    this->temporalFileName = std::string(FILE_LOCK) + std::to_string(this->actionID);
    callsActions = new SharedMemory<int>(FILE,this->actionID);
    if (this->isEmpty() && callsActions->numberOfAttachedProcesses() == 1) {
        this->end();
    }
    lockFile = new LockFile(this->temporalFileName);
}

Action::~Action() {
    delete lockFile;
    if (callsActions->numberOfAttachedProcesses() == 1) {
        this->end();
    }
    delete callsActions;
}

std::string Action::readFile() const {
    //TODO: [Se necesita un semaforo?]
    //Semaphore semaphore(FILE,'s',1);

    //semaphore.wait();
        std::ifstream ifs(this->temporalFileName);
        std::string plainActions( (std::istreambuf_iterator<char>(ifs) ), (std::istreambuf_iterator<char>() ) );
        ifs.close();
    //semaphore.signal();

    return plainActions;
}

void Action::writeInLock(const std::string& text) {
    if (this->lockFile != NULL) {
        lockFile->lock();
        lockFile->Write(text);
        lockFile->free();
    }
}

std::vector<int> Action::getVector() const {
    std::string plainActions = this->readFile();
    std::vector<std::string> listActionsString = Utils::splitString(plainActions,std::string(ACTION_ID_SEPARATOR));
    std::vector<int> listActionsId;
    for (std::string& id : listActionsString ) {
        listActionsId.push_back( atoi(id.c_str()) );
    }
    return listActionsId;
}

int Action::count() const {
    return callsActions->read();
}

void Action::doAction(const int id) {
    std::string callActionString = ((this->count() > 0) ? ACTION_ID_SEPARATOR : "") + std::to_string(id);
    this->writeInLock(callActionString);
    callsActions->write(callsActions->read() + 1);
}

int Action::getFirstId() const {
    if (this->isEmpty()) {
        return -1;
    }
    std::vector<int> vectorId = this->getVector();
    return vectorId[0];
}

int Action::getLastId() const {
    if (this->isEmpty()) {
        return -1;
    }
    std::vector<int> vectorId = this->getVector();
    return vectorId[vectorId.size() - 1];
}

bool Action::isEmpty() const {
    return (this->count() == 0);
}

bool Action::didAction(const int id) {
    std::vector<int> actions = this->getVector();
    for (int& actionId : actions) {
        if (actionId == id) {
            return true;
        }
    }
    return false;
}

int Action::getIdPosition(int id) {
    std::vector<int> actions = this->getVector();
    int position = 0;
    for (int& actionId : actions) {
        if (actionId == id) {
            return position;
        }
        position++;
    }
    return -1;
}

void Action::end() {
    std::remove(this->temporalFileName.c_str());
}