cmake_minimum_required(VERSION 2.6)
project(concurrentes)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(concudaring
	game/Card.cpp
	game/DaringGame.cpp
	game/Player.cpp
	game/TurnManager.cpp
	signals/SIGINT_Handler.cpp
	signals/SignalHandler.cpp
	util/BarrierSimple.cpp
	util/Semaphore.cpp
	util/Thread.cpp
		util/SharedMemory.cpp util/LockFile.cpp util/LockFile.h util/Utils.cpp util/Utils.h Log/Log.cpp Log/Log.h)

add_executable(tp
	main.cpp)
	
add_executable(tp-threaded
	threaded-version.cpp)

target_link_libraries(concudaring pthread)

target_link_libraries(tp concudaring)
target_link_libraries(tp-threaded concudaring)