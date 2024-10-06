cmake_minimum_required (VERSION 3.11)
add_subdirectory(FTXUI-5.0.0) 
project(Work1_grad3 LANGUAGES CXX VERSION 1.0.0)
 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -Wall")
add_executable(main main.cpp tests.cpp)

target_link_libraries(main
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component # Not needed for this example.
)