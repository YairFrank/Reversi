cmake_minimum_required(VERSION 3.5.1)
project(revtest)
set(CMAKE_CXX_STANDARD 98)
enable_testing()

add_subdirectory(test_lib/gtest-1.8.0)
add_subdirectory(Tests)


