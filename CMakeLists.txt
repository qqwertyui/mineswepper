cmake_minimum_required(VERSION 3.18.4)

project(Mineswepper VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

file(GLOB SRC_FILES *.cpp)

add_executable(mineswepper ${SRC_FILES})
target_link_libraries(mineswepper PUBLIC sfml-main)
target_link_libraries(mineswepper PUBLIC sfml-system)
target_link_libraries(mineswepper PUBLIC sfml-graphics)
target_link_libraries(mineswepper PUBLIC sfml-window)