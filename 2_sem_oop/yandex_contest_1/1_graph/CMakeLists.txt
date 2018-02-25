cmake_minimum_required(VERSION 3.9)
project(1_graph)

set(CMAKE_CXX_STANDARD 11)

add_executable(1_graph main.cpp IGraph.h HashGraph.h HashGraph.cpp)