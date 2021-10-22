cmake_minimum_required(VERSION 3.0)
project(Face_Detection_and_Tracking)

set(CMAKE_CXX_STANDARD 14)

#find_library(OpenCV)
find_package(OpenCV)

include_directories(${OpenCV_INCLUDE_DIRS})
set(CMAKE_CXX_STANDARD 11)

add_executable(Face_Detection_and_Tracking main.cpp)
target_link_libraries(Face_Detection_and_Tracking ${OpenCV_LIBS})