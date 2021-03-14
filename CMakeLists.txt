cmake_minimum_required(VERSION 3.2)

project(learning-cpp)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

include(AddCpp)

add_subdirectory(win)

add_cpp(memory)
add_cpp(apply)