cmake_minimum_required(VERSION 3.12)

project(DigitRecognition VERSION 1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME} create_training.cpp)

find_package(OpenCV REQUIRED)

if (OpenCV_FOUND)
    target_include_directories(${PROJECT_NAME} PUBLIC ${OPENCV_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
endif()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/digits.png
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
