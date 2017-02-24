cmake_minimum_required(VERSION 3.5)
project(network2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    network.cpp
    network.h
    social_network.cpp
    user.cpp
    user.h)

add_executable(network2 ${SOURCE_FILES})