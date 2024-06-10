cmake_minimum_required(VERSION 3.10)
project(Work4)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -Wall -ggdb")
add_executable(main 
main.cpp
test.cpp
interface/StartTestCommand.cpp
interface/StartDialogCommand.cpp
../ExtendedMenu/Menu.cpp 
../ExtendedMenu/MenuElement.cpp 

)