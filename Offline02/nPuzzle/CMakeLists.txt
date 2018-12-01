cmake_minimum_required(VERSION 3.12)
project(nPuzzle)

set(CMAKE_CXX_STANDARD 17)

add_executable(nPuzzle Node.h AStarSearch.h main.cpp)
add_executable(GitHub n-puzzle.cpp)
add_executable(Test test.cpp)