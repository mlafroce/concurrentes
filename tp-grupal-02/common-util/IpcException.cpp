#include "IpcException.h"
#include <cstring>

IpcException::IpcException(int err) :
    std::runtime_error(strerror(err)) {    
}
