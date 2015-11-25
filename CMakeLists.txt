cmake_minimum_required(VERSION 2.6)

#=============================#
#      Setup Project          #
#=============================#
project (clisp C)
add_subdirectory(src)

# define folders
get_filename_component(CLISP_DIR "${CMAKE_CURRENT_SOURCE_DIR}" PATH)


set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(EXECUTABLE_OUTPUT_PATH ${CLISP_DIR}/build)

#=============================#
#     Dependencies            #
#=============================#
include_directories(${CLISP_DIR}/ext/mpc)

#=============================#
#     Setup Source            #
#=============================#
set(CLISP_SOURCE_DIR ${CLISP_DIR}/src)

set(CLISP_SOURCES
    ${CLISP_SOURCE_DIR}/ast.c
    ${CLISP_SOURCE_DIR}/builtin.c
    ${CLISP_SOURCE_DIR}/environment.c
    ${CLISP_SOURCE_DIR}/print.c
    ${CLISP_SOURCE_DIR}/repl.c
    ${CLISP_SOURCE_DIR}/token.c
    ${CLISP_SOURCE_DIR}/utils.c
)

set(CLISP_HEADERS
    ${CLISP_SOURCE_DIR}/ast.h
    ${CLISP_SOURCE_DIR}/builtin.h
    ${CLISP_SOURCE_DIR}/environment.h
    ${CLISP_SOURCE_DIR}/error.h
    ${CLISP_SOURCE_DIR}/print.h
    ${CLISP_SOURCE_DIR}/token.h
    ${CLISP_SOURCE_DIR}/utils.h
)

add_executable(repl ${CLISP_SOURCES} ${CLISP_HEADERS)
