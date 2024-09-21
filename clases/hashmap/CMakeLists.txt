cmake_minimum_required(VERSION 3.27)
project(forwardList)

set(CMAKE_CXX_STANDARD 14)

add_executable(main hashmap.cpp)
add_executable(morse morse.cpp)
add_executable(anagrama anagrama.cpp)
add_executable(sudoku sudoku.cpp)
add_executable(sudoku2 sudoku2.cpp)