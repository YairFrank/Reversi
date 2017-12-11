cmake_minimum_required(VERSION 3.8)

project (root)

add_subdirectory(Client)

add_subdirectory(Server)

add_subdirectory(reversi_test)

#Add executable to assignment
file(GLOB Reversi_Sources ${Reversi_SOURCE_DIR}/*.cpp)

set(Reversi_SOURCE_FILES ${Reversi_Sources})

