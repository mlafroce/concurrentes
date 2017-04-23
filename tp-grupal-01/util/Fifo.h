#ifndef CONCURRENTES_FIFO_H
#define CONCURRENTES_FIFO_H

#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

class Fifo {
public:
    Fifo(const std::string name_fifo);
    virtual ~Fifo();
    virtual void Open() = 0;
    void Close();
    void Delete() const;

protected:
    std::string name;
    int fd;
};

class FifoWriting : public Fifo {
public:
    FifoWriting(const std::string name);
    ~FifoWriting();

    void Open();
    ssize_t Write(const void* buffer,const ssize_t buffsize) const;
};

class FifoReading : public Fifo {
public:
    FifoReading(const std::string name);
    ~FifoReading();

    void Open();
    ssize_t Read(void* buffer,const ssize_t buffsize) const;
};

#endif //CONCURRENTES_FIFO_H
