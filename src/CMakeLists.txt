cmake_minimum_required(VERSION 3.12)

project(Sudoku VERSION 1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp
	board.cpp utils.cpp solver.cpp view_sfml.cpp game.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

if (SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
endif()

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_project_warnings(${PROJECT_NAME})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets/arial.ttf
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
