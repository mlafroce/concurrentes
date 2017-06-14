cmake_minimum_required(VERSION 2.6)
project(concurrentes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(db-client-lib
        ../common-util/LockFile.cpp
        ../common-util/Log.cpp
        ../common-util/Semaphore.cpp
        ../common-util/Utils.cpp
        ../common-util/MessageQueue.h ../common-util/message/Message.cpp ../common-util/message/Message.h)

add_executable(db-client main.cpp)

target_link_libraries(db-client db-client-lib)