#include "LockFile.h"

#include <cstring>
#include "Utils.h"



LockFile::LockFile(const std::string &_name):name(_name) {
    this->flock1.l_type     = F_WRLCK;
    this->flock1.l_whence   = SEEK_SET;
    this->flock1.l_start    = 0;
    this->flock1.l_len      = 0;

    this->fd = open(this->name.c_str(), O_CREAT | O_WRONLY, 0777);
    if (this->fd <= 0) {
        Utils::throwError( std::string("Error on open() Lock (create): ") + std::string(strerror(errno)) );
    }
}

int LockFile::lock() {
    this->flock1.l_type = F_WRLCK;
    return fcntl( this->fd,F_SETLKW,&(this->flock1) );
}

int LockFile::free() {
    this->flock1.l_type = F_UNLCK;
    return fcntl(this->fd,F_SETLK,&(this->flock1));
}

ssize_t LockFile::Write(const void* buffer,const ssize_t buffer_size) const {
    lseek(this->fd,0,SEEK_END);
    return write(this->fd,buffer,(size_t)buffer_size);
}

LockFile :: ~LockFile () {
    close(this->fd);
}
