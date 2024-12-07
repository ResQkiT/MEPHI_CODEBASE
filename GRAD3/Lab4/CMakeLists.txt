cmake_minimum_required(VERSION 3.5)

project(Work4_grad3 VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)  
set(CMAKE_CXX_STANDARD_REQUIRED ON)  
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall") 

find_package(Qt5 REQUIRED COMPONENTS Core Widgets)

add_executable(main main.cpp test.cpp util/GraphRenderer.cpp util/ImageRenderer.cpp)

target_link_libraries(main Qt5::Core Qt5::Widgets )