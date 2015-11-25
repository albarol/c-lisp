cmake_minimum_required(VERSION 2.6)

#=============================#
#      Setup Project          #
#=============================#
project (clisp C)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c11")
set(EXE_NAME "clisp")

# define folders
set(CLISP_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MPC_DIR "${CLISP_DIR}/ext/mpc")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CLISP_DIR}/CMake/packages/")
set(EXECUTABLE_OUTPUT_PATH ${CLISP_DIR}/build)

#=============================#
#     Dependencies            #
#=============================#
find_package(edit REQUIRED)
include_directories(${MPC_DIR})

#=============================#
#     Setup Source            #
#=============================#
set(CLISP_SOURCE_DIR ${CLISP_DIR}/src)

set(CLISP_SOURCES
    ${MPC_DIR}/mpc.c
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

#=============================#
#     Setup Output            #
#=============================#

add_executable(${EXE_NAME} ${CLISP_SOURCES} ${CLISP_HEADERS})

if(UNIX)
  target_link_libraries(${EXE_NAME} m)
  target_link_libraries(${EXE_NAME} edit)
endif(UNIX)

link_directories(${CLISP_DIR}/ext/mpc)
