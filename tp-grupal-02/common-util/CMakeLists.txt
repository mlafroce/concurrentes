cmake_minimum_required(VERSION 2.6)
project(concurrentes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(common
        IpcException.cpp
        Log.cpp
        LockFile.cpp
        MessageQueue.cpp
        Utils.cpp
        SharedMemory.cpp
        signals/SIGCHLD_Handler.cpp
        signals/SIGINT_Handler.cpp
        signals/SignalHandler.cpp
        signals/Process.cpp
        message/MessageSender.cpp
        message/Message.cpp)
