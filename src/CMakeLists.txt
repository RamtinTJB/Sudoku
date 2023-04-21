cmake_minimum_required(VERSION 3.12)

project(Sudoku VERSION 1.0 LANGUAGES CXX)

add_subdirectory(digit_recognition_training)
add_subdirectory(assets)

add_executable(${PROJECT_NAME} main.cpp
	board.cpp utils.cpp solver.cpp view_sfml.cpp game.cpp options.cpp image.cpp)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
find_package(OpenCV REQUIRED)

if (SFML_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} sfml-network sfml-audio sfml-graphics sfml-window sfml-system)
endif()

if (OpenCV_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${OPENCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
endif()

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_project_warnings(${PROJECT_NAME})
