cmake_minimum_required(VERSION 3.5)
project(lab_linkedlists)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    delist.cpp
    delist.h
    delist_test.cpp)

add_executable(lab_linkedlists ${SOURCE_FILES})