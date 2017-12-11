project(mainTesting)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${Reversi_SOURCE_DIR})
link_directories(${Reversi_SOURCE_DIR})

file(GLOB Reversi_Sources ${Reversi_SOURCE_DIR}/*.cpp)
file(GLOB Test_Sources ${mainTesting_SOURCE_DIR}/*.cpp)
set(SOURCE_FILES ${Test_Sources} ${Reversi_Sources} BoardTest.cpp AITest.cpp PlayerTest.cpp GameLogicTest.cpp)

list(REMOVE_ITEM SOURCE_FILES ${Reversi_SOURCE_DIR}/Main.cpp)

add_executable(maintest ${SOURCE_FILES} AITest.cpp AITest.cpp PlayerTest.cpp GameLogicTest.cpp)
target_link_libraries(maintest gtest gtest_main)

add_test(test1 maintest)
