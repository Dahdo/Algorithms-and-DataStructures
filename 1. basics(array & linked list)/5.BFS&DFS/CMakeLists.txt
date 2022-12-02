cmake_minimum_required(VERSION 3.23)
project(5_BFS_DFS)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(5_BFS_DFS
        BFS.cpp
        Graph.cpp
        Graph.h)
