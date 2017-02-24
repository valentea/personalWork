cmake_minimum_required(VERSION 3.3)
project(Color_Cov)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Color_Cov ${SOURCE_FILES})