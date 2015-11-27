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
set(PTEST_DIR "${CLISP_DIR}/ext/ptest")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CLISP_DIR}/CMake/packages/")
set(EXECUTABLE_OUTPUT_PATH ${CLISP_DIR}/build)

#=============================#
#     Dependencies            #
#=============================#
find_package(edit REQUIRED)
include_directories(${MPC_DIR})
include_directories(${PTEST_DIR})

#=============================#
#     Setup Source            #
#=============================#
set(CLISP_SOURCE_DIR ${CLISP_DIR}/src)

set(CLISP_SOURCES
    ${MPC_DIR}/mpc.c
    src/ast.c
    src/builtin.c
    src/environment.c
    src/print.c
    src/token.c
    src/utils.c
    src/types.c
)

set(CLISP_HEADERS
    src/ast.h
    src/builtin.h
    src/environment.h
    src/error.h
    src/print.h
    src/token.h
    src/utils.h
    src/types.h
)

#=============================#
#     Setup Output            #
#=============================#

add_executable(${EXE_NAME} ${CLISP_SOURCES} ${CLISP_HEADERS} src/repl.c)

if(UNIX)
  target_link_libraries(${EXE_NAME} m)
  target_link_libraries(${EXE_NAME} edit)
endif(UNIX)

link_directories(${CLISP_DIR}/ext/mpc)

#=============================#
#     Setup Tests             #
#=============================#
set(CLISP_TESTS
    ${PTEST_DIR}/ptest.h
    ${PTEST_DIR}/ptest.c
    tests/test.c
    tests/test_types.c
)
add_executable(clispTest ${CLISP_TESTS} ${CLISP_SOURCES} ${CLISP_HEADERS})

if(UNIX)
    target_link_libraries(clispTest m)
    target_link_libraries(clispTest edit)
endif(UNIX)

link_directories(${PTEST_DIR})