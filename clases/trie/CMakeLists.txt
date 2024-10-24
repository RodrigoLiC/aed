cmake_minimum_required(VERSION 3.27)
project(forwardList)

set(CMAKE_CXX_STANDARD 14)

add_executable(main trie.cpp)
add_executable(main2 k-common.cpp)
add_executable(main3 magic-dict.cpp)
add_executable(main4 suggestion-trie.cpp)