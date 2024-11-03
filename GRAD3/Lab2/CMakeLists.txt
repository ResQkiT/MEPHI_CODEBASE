cmake_minimum_required(VERSION 3.10)

project(Lab2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -Wall")

add_executable(main main.cpp tests.cpp)