cmake_minimum_required(VERSION 3.27)
project(forwardList)

set(CMAKE_CXX_STANDARD 14)

add_executable(main hashmap.cpp)
add_executable(morse morse.cpp)
add_executable(anagrama anagrama.cpp)