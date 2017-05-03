#include <sys/stat.h>
#include <cstring>
#include "Fifo.h"
#include "Utils.h"


Fifo::Fifo(const std::string _name) : name(_name), fd(-1) {
    int result_mknod = mknod ( static_cast<const char*>(name.c_str()),S_IFIFO|0666,0 );
    if (result_mknod == -1){
        THROW_UTIL( std::string("Error en mknod() (constructor): ") + std::string(strerror(errno)) );
    }
}

Fifo::~Fifo() {
    this->Delete();
}

void Fifo::Close() {
    close(fd);
    fd = -1;
}

void Fifo::Delete() const {
    unlink(name.c_str());
}





FifoWriting::FifoWriting(const std::string name) : Fifo(name) {
}

FifoWriting::~FifoWriting() {}

void FifoWriting::Open() {
    fd = open ( name.c_str(),O_WRONLY );
    if (fd == -1){
        THROW_UTIL( std::string("Error en open() (constructor): ") + std::string(strerror(errno)) );
    }
}

ssize_t FifoWriting::Write(const void* buffer,const ssize_t buffer_size) const {
    return write(fd,buffer,(size_t)buffer_size);
}






FifoReading::FifoReading(const std::string name) : Fifo(name) {}

FifoReading::~FifoReading() {}

void FifoReading::Open() {
    fd = open( name.c_str(),O_RDONLY );
    if (fd == -1){
        THROW_UTIL( std::string("Error en open() (constructor): ") + std::string(strerror(errno)) );
    }
}

ssize_t FifoReading::Read(void* buffer,const ssize_t buffer_size) const {
    return read(fd,buffer,(size_t)buffer_size);
}


