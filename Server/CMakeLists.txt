cmake_minimum_required(VERSION 3.8)
project(Server)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS -pthread)

set(SOURCE_FILES main.cpp Command.h StartCommand.cpp JoinCommand.cpp StartCommand.h List_gamesCommand.cpp List_gamesCommand.h JoinCommand.h GamesList.cpp GamesList.h Server.cpp Server.h CommandsManager.cpp CommandsManager.h)
add_executable(Server ${SOURCE_FILES})