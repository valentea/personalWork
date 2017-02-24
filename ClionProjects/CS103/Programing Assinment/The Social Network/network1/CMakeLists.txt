cmake_minimum_required(VERSION 3.5)
project(network1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES
    network.cpp
    network.h
    social_network.cpp
    user.cpp
    user.h)

add_executable(network1 ${SOURCE_FILES})