cmake_minimum_required(VERSION 2.6)
project(concurrentes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(concudaring
	game/Card.cpp
	game/DaringGame.cpp
	game/Player.cpp
	game/TurnManager.cpp
	game/action/Action.cpp
	game/action/HandAction.cpp
	game/action/SimpleAction.cpp
	signals/SIGINT_Handler.cpp
	signals/SignalHandler.cpp
	util/BarrierSimple.cpp
	util/Fifo.cpp
	util/Pipe.cpp
	util/Semaphore.cpp
	util/SharedMemory.cpp
	util/LockFile.cpp
	util/Utils.cpp
        log/Log.cpp
        game/Table.cpp game/Table.h game/Referee.cpp game/Referee.h)

add_executable(tp
	main.cpp)


target_link_libraries(concudaring pthread)

target_link_libraries(tp concudaring)