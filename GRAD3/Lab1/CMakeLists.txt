cmake_minimum_required(VERSION 3.11)
project(Work1_grad3 LANGUAGES CXX VERSION 1.0.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -Wall")

include(FetchContent)

# Fetch FTXUI
FetchContent_Declare(
  ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
  GIT_TAG v5.0.0 # Use the appropriate tag or branch
)

FetchContent_MakeAvailable(ftxui)

add_executable(main main.cpp tests.cpp)

target_link_libraries(main
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)