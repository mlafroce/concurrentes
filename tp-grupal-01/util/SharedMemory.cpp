#include "SharedMemory.h"
#include "Utils.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

SharedMemoryBase::SharedMemoryBase(int shmid, void* ptrData) :
	shmId(shmid), ptrData(ptrData) {}
	
SharedMemoryBase::SharedMemoryBase(int shmid) : shmId(shmid) {}

SharedMemoryBase::~SharedMemoryBase () {
    this->detach();
}

void SharedMemoryBase::create(const std::string& file, const char letter, size_t dataSize) {
    key_t key = Utils::generateKey(file,letter);

    this->shmId = shmget(key, dataSize, 0644|IPC_CREAT);
    if (this->shmId < 1) {
        Utils::throwError( std::string("Error on shmget(): ") + std::string(strerror(errno)) );
    }
    this->attach();
}

void SharedMemoryBase::attach() {
    void* tmpPtr = shmat(this->shmId,NULL,0);
    if ( tmpPtr == (void*) -1 ) {
        Utils::throwError( std::string("Error en shmat(): ") + std::string(strerror(errno)) );
    }
    this->ptrData =  tmpPtr;
}

void SharedMemoryBase::detach() {
    int errorDt = shmdt((void *) this->ptrData);
    if (errorDt == -1) {
        Utils::throwError( std::string("Error on shmdt(): ") + std::string(strerror(errno)) );
    }

    if ( this->numberOfAttachedProcesses() == 0 ) {
        shmctl (this->shmId,IPC_RMID,NULL);
    }
}

int SharedMemoryBase::numberOfAttachedProcesses() const {
    shmid_ds state;
    shmctl(this->shmId,IPC_STAT,&state );
    return (int) state.shm_nattch;
}
