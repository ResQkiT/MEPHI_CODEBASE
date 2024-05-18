cmake_minimum_required(VERSION 3.10)
project(TestMenu)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -Wall")
add_executable(testmenu testmenu.cpp ICommand.cpp Menu.cpp MenuElement.cpp PrintHelloCommand.cpp)