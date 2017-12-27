cmake_minimum_required(VERSION 3.8)
project(Server)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp Server.cpp Server.h StartCommand.cpp JoinCommand.cpp PlayCommand.cpp CloseCommand.cpp StartCommand.h List_gamesCommand.cpp List_gamesCommand.h CloseCommand.h JoinCommand.h PlayCommand.h GamesList.cpp GamesList.h)
add_executable(Server ${SOURCE_FILES})