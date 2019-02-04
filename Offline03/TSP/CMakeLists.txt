# cmake_minimum_required(VERSION <specify CMake version here>)
project(TSP)

set(CMAKE_CXX_STANDARD 17)

add_executable(TSP main.cpp tspDS.h Heuristics.h)

add_executable(Dataset Dataset.cpp tspDS.h Heuristics.h HeuristicsRandomized.h)