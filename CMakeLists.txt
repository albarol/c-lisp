cmake_minimum_required(VERSION 2.6)

#=============================#
#      Setup Project          #
#=============================#
project (clisp C)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c11")

# define folders
set(MPC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ext/mpc")
set(PTEST_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ext/ptest")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/CMake/packages/")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build)

# define compile rules
OPTION(WITH_PRELUDE "Prelude." OFF)
IF(WITH_PRELUDE)
    add_definitions(-DHAVE_PRELUDE)
    execute_process(COMMAND "xxd -i ${CMAKE_CURRENT_SOURCE_DIR}/stl/prelude.clisp > /tmp/prelude.c" OUTPUT_VARIABLE STL_PRELUDE)
ENDIF(WITH_PRELUDE)

#=============================#
#     Dependencies            #
#=============================#
find_package(edit REQUIRED)
include_directories(${MPC_DIR})
include_directories(${PTEST_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

#=============================#
#     Setup Source            #
#=============================#
set(CLISP_SOURCES
    ${MPC_DIR}/mpc.c
    src/ast/eval.c
    src/ast/read.c
    src/builtin.c
    src/builtin/bool.c
    src/builtin/exception.c
    src/builtin/io.c
    src/builtin/list.c
    src/builtin/magic.c
    src/builtin/math.c
    src/builtin/number.c
    src/builtin/string.c
    src/builtin/syntactic.c
    src/core/print.c
    src/core/utils.c
    src/core/types.c
    src/core/env.c
    src/core/expr.c
)
IF(WITH_PRELUDE)
    set(CLISP_SOURCES ${CLISP_SOURCES} /tmp/prelude.c)
ENDIF(WITH_PRELUDE)

set(CLISP_HEADERS
    include/ast.h
    include/builtin.h
    include/error.h
    include/print.h
    include/types.h
    include/utils.h
    include/stl.h
)

#=============================#
#     Setup Output            #
#=============================#

add_executable(clisp ${CLISP_SOURCES} ${CLISP_HEADERS} src/repl.c)

target_link_libraries(clisp m)
target_link_libraries(clisp edit)


#=============================#
#     Setup Tests             #
#=============================#
set(CLISP_TESTS
    ${PTEST_DIR}/ptest.h
    ${PTEST_DIR}/ptest.c
    tests/unit/test.c
    tests/unit/test_types.c
    tests/unit/test_env.c
    tests/unit/test_expr.c
    tests/unit/builtin/test_builtin_bool.c
    tests/unit/builtin/test_builtin_exception.c
    tests/unit/builtin/test_builtin_io.c
    tests/unit/builtin/test_builtin_list.c
    tests/unit/builtin/test_builtin_math.c
    tests/unit/builtin/test_builtin_number.c
    tests/unit/builtin/test_builtin_string.c
    tests/unit/builtin/test_builtin_syntactic.c
    tests/unit/ast/test_ast.c
    tests/unit/ast/test_builtin_list.c
    tests/unit/ast/test_builtin_math.c
    tests/unit/ast/test_builtin_ordering.c
    tests/unit/ast/test_builtin_comparison.c
    tests/unit/ast/test_builtin_conditionals.c
    tests/unit/helper.c
)
add_executable(clispTest ${CLISP_TESTS} ${CLISP_SOURCES} ${CLISP_HEADERS})

if(UNIX)
    target_link_libraries(clispTest m)
    target_link_libraries(clispTest edit)
endif(UNIX)