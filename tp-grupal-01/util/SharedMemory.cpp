#include "SharedMemory.h"
#include "Utils.h"

#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <iostream>

template <class T> SharedMemory<T>::SharedMemory ():shmId(0),ptrData(NULL) {}

template <class T> void SharedMemory<T>::create ( const std::string& file,const char letter ) {
    key_t key = Utils::generateKey(file,letter);

    this->shmId = shmget(key,sizeof(T),0644|IPC_CREAT);
    if (this->shmId < 1) {
        Utils::throwError( std::string("Error on shmget(): ") + std::string(strerror(errno)) );
    }

    this->attach();
}

template <class T> void SharedMemory<T>::attach() {
    void* tmpPtr = shmat(this->shmId,NULL,0);
    if ( tmpPtr == (void*) -1 ) {
        Utils::throwError( std::string("Error en shmat(): ") + std::string(strerror(errno)) );
    }
    this->ptrData = static_cast<T*> (tmpPtr);
}

template <class T> void SharedMemory<T>::detach() {
    int errorDt = shmdt((void *) this->ptrData);
    if (errorDt == -1) {
        Utils::throwError( std::string("Error on shmdt(): ") + std::string(strerror(errno)) );
    }

    if ( this->numberOfAttachedProcesses() == 0 ) {
        shmctl (this->shmId,IPC_RMID,NULL);
    }
}

template <class T> SharedMemory<T>::SharedMemory ( const std::string& file,const char letter ):shmId(0),ptrData(NULL) {
    this->create(file,letter);
}

template <class T> SharedMemory<T>::SharedMemory ( const SharedMemory& other ):shmId(other.shmId) {
    this->attach();
}

template <class T> void SharedMemory<T>::write ( const T& data ) {
    *(this->ptrData) = data;
}

template <class T> T SharedMemory<T>::read() const {
    return *(this->ptrData);
}

template <class T> int SharedMemory<T> ::numberOfAttachedProcesses() const {
    shmid_ds state;
    shmctl(this->shmId,IPC_STAT,&state );
    return (int) state.shm_nattch;
}

template <class T> SharedMemory<T>& SharedMemory<T>::operator= ( const SharedMemory& other ) {
    this->shmId = other.shmId;
    this->attach();
    return *this;
}

template <class T> SharedMemory<T>::~SharedMemory () {
    this->detach();
}
