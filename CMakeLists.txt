cmake_minimum_required(VERSION 3.18.4)

project(Mineswepper VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_executable(mineswepper main.cpp Minefield.cpp)
target_link_libraries(mineswepper PUBLIC sfml-main)
target_link_libraries(mineswepper PUBLIC sfml-system)
target_link_libraries(mineswepper PUBLIC sfml-graphics)
target_link_libraries(mineswepper PUBLIC sfml-window)