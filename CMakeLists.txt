cmake_minimum_required(VERSION 3.21)
project(challenge)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(unit-test)
add_executable(challenge main.cpp add.h add.cpp find-largest-sum.h find-largest-sum.cpp)