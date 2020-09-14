cmake_minimum_required(VERSION 2.8)

include_directories(../lib)

set(SRCS t_stats_15_3.c file_perms.c)
add_executable(t_stats_15_3 ${SRCS})
target_link_libraries(t_stats_15_3 tlpi_lib)

set(SRCS check_access_15_4.c file_perms.c)
add_executable(check_access_15_4 ${SRCS})
target_link_libraries(check_access_15_4 tlpi_lib)

set(SRCS get_umask_15_5.c file_perms.c)
add_executable(get_umask_15_5 ${SRCS})
target_link_libraries(get_umask_15_5 tlpi_lib)

set(SRCS chmodarx_15_6.c file_perms.c)
add_executable(chmodarx_15_6 ${SRCS})
target_link_libraries(chmodarx_15_6 tlpi_lib)

set(SRCS chattr_15_7.c file_perms.c)
add_executable(chattr_15_7 ${SRCS})
target_link_libraries(chattr_15_7 tlpi_lib)

