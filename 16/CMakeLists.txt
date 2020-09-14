cmake_minimum_required(VERSION 2.8)

include_directories(../lib)

set(SRCS setuserxattr_16_1.c)
add_executable(setuserxattr_16_1 ${SRCS})
target_link_libraries(setuserxattr_16_1 tlpi_lib)

