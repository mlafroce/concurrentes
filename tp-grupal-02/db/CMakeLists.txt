cmake_minimum_required(VERSION 2.6)
project(concurrentes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(db-server
    core/Table.cpp
    core/Server.cpp
    server.cpp # main()
)

add_executable(db-client
    core/Client.cpp
    client.cpp # main()
)

target_link_libraries(db-server common)
target_link_libraries(db-client common)


