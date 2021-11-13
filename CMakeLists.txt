cmake_minimum_required(VERSION 3.20)
project(RM)
find_package(RapidJSON REQUIRED)

set(CMAKE_CXX_STANDARD 11)
include_directories("./")
add_executable(RM main.cpp)

