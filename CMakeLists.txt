cmake_minimum_required(VERSION 2.8)

set(CMAKE_C_COMPILER gcc)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")

add_subdirectory(lib)
add_subdirectory(15)
add_subdirectory(16)
