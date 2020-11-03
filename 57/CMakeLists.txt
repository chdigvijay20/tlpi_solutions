cmake_minimum_required(VERSION 2.8)

include_directories(../lib)

set(SRCS fast_client_57_1.c)
add_executable(fast_client_57_1 ${SRCS})
target_link_libraries(fast_client_57_1 tlpi_lib)

set(SRCS slow_server_57_1.c)
add_executable(slow_server_57_1 ${SRCS})
target_link_libraries(slow_server_57_1 tlpi_lib)

set(SRCS us_abstract_bind_sv_57_2.c)
add_executable(us_abstract_bind_sv_57_2 ${SRCS})
target_link_libraries(us_abstract_bind_sv_57_2 tlpi_lib)

set(SRCS us_abstract_bind_cl_57_2.c)
add_executable(us_abstract_bind_cl_57_2 ${SRCS})
target_link_libraries(us_abstract_bind_cl_57_2 tlpi_lib)

set(SRCS sequence_num_server_57_3.c)
add_executable(sequence_num_server_57_3 ${SRCS})
target_link_libraries(sequence_num_server_57_3 tlpi_lib)

set(SRCS sequence_num_client_57_3.c)
add_executable(sequence_num_client_57_3 ${SRCS})
target_link_libraries(sequence_num_client_57_3 tlpi_lib)

set(SRCS socket_a_57_4.c)
add_executable(socket_a_57_4 ${SRCS})
target_link_libraries(socket_a_57_4 tlpi_lib)

set(SRCS socket_b_57_4.c)
add_executable(socket_b_57_4 ${SRCS})
target_link_libraries(socket_b_57_4 tlpi_lib)

set(SRCS socket_c_57_4.c)
add_executable(socket_c_57_4 ${SRCS})
target_link_libraries(socket_c_57_4 tlpi_lib)
