#ifndef CONCURRENTES_MESSAGEQUEUE_H
#define CONCURRENTES_MESSAGEQUEUE_H

#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include "Utils.h"

template <class T> class MessageQueue {
private:
    key_t	key;
    int		id;

public:
    MessageQueue ( const std::string& file,const char letter );
    ~MessageQueue();
    int write ( const T& dato ) const;
    int read ( const int tipo,T* buffer ) const;
    int destroy () const;
};

template <class T> MessageQueue<T>::MessageQueue(const std::string& file, const char letter) {
    this->key = Utils::generateKey(file,letter)
    this->id = msgget ( this->key,0777|IPC_CREAT );
    if ( this->id == -1 )
        THROW_UTIL( std::string("Error en msgget(): ") + std::string(strerror(errno)) );
}

template <class T> MessageQueue<T>::~MessageQueue () {
}

template <class T> int MessageQueue<T>::destroy() const {
    return msgctl(this->id,IPC_RMID,NULL);
}

template <class T> int MessageQueue<T>::write( const T& dato ) const {
    return msgsnd(this->id,static_cast<const void*>(&dato),sizeof(T)-sizeof(long),0 );
}

template <class T> int MessageQueue<T>::read( const int tipo,T* buffer ) const {
    return (int)msgrcv(this->id,static_cast<void *>(buffer),sizeof(T)-sizeof(long),tipo,0);
}


#endif //CONCURRENTES_MESSAGEQUEUE_H
