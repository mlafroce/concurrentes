#ifndef CONCURRENTES_LOCKFILE_H
#define CONCURRENTES_LOCKFILE_H

#include <unistd.h>
#include <fcntl.h>
#include <string>


class LockFile {
public:
    LockFile(const std::string& name);
    ~LockFile();

    int lock();
    int readLock();
    int free();
    int readFree();

    ssize_t Write(const void* buffer, const ssize_t buffer_size) const;
    ssize_t Write(const std::string& buffer) const;

private:
    struct flock flock1;
    int fd;
    std::string name;
};


#endif //CONCURRENTES_LOCKFILE_H
