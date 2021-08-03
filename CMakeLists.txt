cmake_minimum_required(VERSION 3.2)

project(learning-cpp)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(PROJECTS "" CACHE INTERNAL "")

function(add_cpp NAME)
   add_executable(${NAME} "${NAME}.cpp")
   set(PROJECTS "${PROJECTS};${NAME}|${CMAKE_CURRENT_BINARY_DIR}" CACHE INTERNAL "")
endfunction()

add_cpp(api)
add_cpp(apply)
add_cpp(concurrency)
add_cpp(decltype)
add_cpp(functors)
# add_cpp(memory)
add_cpp(regex)
add_cpp(shared_ptr)
add_cpp(template)

file(GENERATE OUTPUT ${CMAKE_SOURCE_DIR}/data CONTENT "$<TARGET_NAME:${CMAKE_BINARY_DIR}\n${PROJECTS}>")