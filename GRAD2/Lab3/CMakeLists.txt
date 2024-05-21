cmake_minimum_required(VERSION 3.10)
project(Work3)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -Wall")
add_executable(main 
interface/StartTestCommand.cpp
interface/StartDialogCommand.cpp
interface/RunFunctionCommand.cpp 
../ExtendedMenu/Menu.cpp 
../ExtendedMenu/MenuElement.cpp 
main.cpp test.cpp 
entities/Person.cpp entities/Student.cpp )