cmake_minimum_required(VERSION 3.9)
project(assembler)

set(CMAKE_C_STANDARD 90)

link_directories(${PROJECT_SOURCE_DIR}/libft/pf)
include_directories(${PROJECT_SOURCE_DIR}/libft/pf)
link_directories(${PROJECT_SOURCE_DIR}/libft)
include_directories(${PROJECT_SOURCE_DIR}/libft)

add_executable(assembler
        asm.h
        asm_true.h
        ft_arg_join.c
        ft_hex.c
        ft_swp_bits.c
        ft_write_in.c
        helpers.c
        op.h
        parse.c
        print.c
        start.c
        utils.c
        Makefile)

target_link_libraries(assembler ${PROJECT_SOURCE_DIR}/libft/libft.a)
#set(CMAKE_C_FLAGS "-lncurses")