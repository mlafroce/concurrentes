#include "IpcException.h"
#include "Log.h"
#include <cstring>

IpcException::IpcException(int err) :
    std::runtime_error(strerror(err)) {
    LOG_ERROR(std::string(strerror(err)));
}
