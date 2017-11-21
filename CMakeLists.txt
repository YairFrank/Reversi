cmake_minimum_required(VERSION 3.8)
project(Targil1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Board.cpp Board.h Player.cpp Player.h Disc.cpp Disc.h ReversiGame.cpp ReversiGame.h ReversiGameLogic.cpp ReversiGameLogic.h Gamer.h)
add_executable(Targil1 ${SOURCE_FILES})