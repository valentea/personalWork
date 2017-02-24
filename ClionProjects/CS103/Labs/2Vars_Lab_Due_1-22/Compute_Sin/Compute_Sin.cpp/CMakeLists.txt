cmake_minimum_required(VERSION 3.3)
project(Compute_Sin_cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Main.cpp)

add_executable(Compute_Sin_cpp ${SOURCE_FILES})