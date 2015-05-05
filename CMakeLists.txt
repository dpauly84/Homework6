cmake_minimum_required(VERSION 3.2)
project(Trial6)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES classlist.cpp)
add_executable(Trial6 ${SOURCE_FILES} classlist.hpp bin_search_tree.hpp bin_search_tree.cpp)