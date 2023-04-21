cmake_minimum_required(VERSION 3.12)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/arial.ttf
            ${CMAKE_CURRENT_SOURCE_DIR}/sudoku.jpg
            ${CMAKE_CURRENT_SOURCE_DIR}/sudoku1.jpg
            ${CMAKE_CURRENT_SOURCE_DIR}/sudoku.sdk
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
