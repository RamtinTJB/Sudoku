cmake_minimum_required(VERSION 3.12)

project(Sudoku VERSION 1.0 LANGUAGES CXX)

include (cmake/FindSFML.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
