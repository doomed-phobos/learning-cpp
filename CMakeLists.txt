cmake_minimum_required(VERSION 3.2)

project(learning-cpp)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

include(AddCpp)

add_subdirectory(win)

add_cpp(memory)