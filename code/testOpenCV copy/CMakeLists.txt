cmake_minimum_required(VERSION 3.20)
project(testOpenCV)

set(CMAKE_CXX_STANDARD 14)

#find_library(OpenCV)
find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

add_executable(testOpenCV main.cpp BinarySearchTree.cpp LinkedList.cpp)

target_link_libraries(testOpenCV ${OpenCV_LIBS})