#ifndef IPCEXCEPTION_H
#define IPCEXCEPTION_H

#include <stdexcept>

class IpcException : public std::runtime_error {
public:
    IpcException(int err);
};

#endif // IPCEXCEPTION_H
