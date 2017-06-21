cmake_minimum_required(VERSION 2.6)
project(concurrentes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(common
    IpcException.cpp
    Log.cpp
    LockFile.cpp
    MessageQueue.cpp
    Semaphore.cpp
    Utils.cpp
    message/Message.cpp
    signals/SIGINT_Handler.cpp
    signals/SignalHandler.cpp
    signals/Process.cpp
)