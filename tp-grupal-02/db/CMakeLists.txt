cmake_minimum_required(VERSION 2.6)
project(concurrentes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(db-lib
        core/Table.cpp core/Table.h
        ../common-util/LockFile.cpp ../common-util/LockFile.h
        ../common-util/Log.cpp ../common-util/Log.h
        ../common-util/Semaphore.cpp ../common-util/Semaphore.h
        ../common-util/Utils.cpp ../common-util/Utils.h
        ../common-util/MessageQueue.h
        ../common-util/message/Message.cpp ../common-util/message/Message.h)

add_executable(db main.cpp utils/TextTable.h)

target_link_libraries(db db-lib)


