cmake_minimum_required(VERSION 3.10)
project(Work2)
 
find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE) # not defined in CONFIG mode
    include(${wxWidgets_USE_FILE})
endif()
add_executable(myapp myapp.cpp)
target_link_libraries(myapp ${wxWidgets_LIBRARIES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -Wall")
add_executable(main main.cpp test.cpp)