cmake_minimum_required(VERSION 3.5)
project(amaze)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        maze.cpp
        mazeio.cpp
        mazeio.h
        queue.cpp
        queue.h)

add_executable(amaze ${SOURCE_FILES})