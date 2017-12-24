cmake_minimum_required(VERSION 3.8)
project(Reversi)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-std=gnu++0x)

set(SOURCE_FILES
        Board.cpp
        Board.h
        ConsoleDisplayer.cpp
        ConsoleDisplayer.h
        Displayer.cpp
        Displayer.h
        GameLogic.cpp
        GameLogic.h
        Main.cpp
        HumanPlayer.cpp
        ReversieGame.cpp
        ReversieGame.h
        Shortcuts.h AIPlayer.cpp AIPlayer.h Player.cpp Menu.cpp Menu.h Player.h HumanPlayer.h Client.cpp Client.h RemotePlayer.cpp RemotePlayer.h RemoteGame.cpp RemoteGame.h Command.h PrintCommand.h CommandsManager.cpp CommandsManager.h)

add_executable(Reversi ${SOURCE_FILES})