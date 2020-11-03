cmake_minimum_required(VERSION 2.8)

set(SRCS error_functions.c get_num.c ugid_functions.c)

add_library(tlpi_lib ${SRCS})
